-- Cleanup previously existing schema.
DROP TABLE IF EXISTS transfer CASCADE;
DROP TABLE IF EXISTS account;
DROP PROCEDURE IF EXISTS transfer;

-- Main account table.
-- Simplistic structure only for sake of test.
CREATE TABLE IF NOT EXISTS account (
    uid UUID PRIMARY KEY,
    balance DECIMAL(14, 2));

-- A log kind of table.
-- Useful to trace movement of currency.
CREATE TABLE IF NOT EXISTS transfer (
    uid UUID PRIMARY KEY,
    src UUID FOREIGN KEY REFERENCES account(uid),
    dst UUID FOREIGN KEY REFERENCES account(uid),
    amount DECIMAL(14, 2),
    time TIMESTAMP WITH TIME ZONE);

-- Main transfer procedure.
-- It is atomic, means it is a TRANSACTION or savepoint in other TRANSACTION.
-- Atomicity & consistency is the key here, because concurrent updates will not prevail.
CREATE PROCEDURE transfer (IN src UUID, IN dst UUID, IN amount DECIMAL(12,2))
MODIFIES SQL DATA
BEGIN ATOMIC
    DECLARE var_src_balance DECIMAL(14,2);

    IF src = dst THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'DST_ACCOUNT_IS_SRC';
    END IF;

    IF NOT EXISTS(SELECT * FROM account WHERE uid = src) THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'SRC_ACCOUNT_DOES_NOT_EXIST';
    END IF;

    IF NOT EXISTS(SELECT * FROM account WHERE uid = dst) THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'DST_ACCOUNT_DOES_NOT_EXIST';
    END IF;

    -- Check original balance.
    SELECT balance
    INTO var_src_balance
    FROM account
    WHERE uid = src;

    -- Check balance to be okay.
    -- If not, throw exception.
    IF var_src_balance < amount THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'NOT_ENOUGH_MONEY_ON_ACCOUNT';
    END IF;

    -- Remove amount from src account.
    UPDATE account
    SET balance = balance - amount
    WHERE uid = src;

    -- Add amount to dst account.
    UPDATE account
    SET balance = balance + amount
    WHERE uid = dst;

    -- Record operation into transfer logs.
    INSERT INTO transfer (uid, src, dst, amount, time)
    VALUES (UUID(), src, dst, amount, CURRENT_TIMESTAMP);
END;

-- Create 2 basic accounts.
INSERT INTO account (uid, balance)
VALUES (UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), 1000.50);

INSERT INTO account (uid, balance)
VALUES (UUID('65f12b00-ac45-40fe-9f4e-16989522f8af'), 999.99);

INSERT INTO account (uid, balance)
VALUES (UUID('3c4f845f-f87f-4b77-afe7-5164a902b242'), 999999999999.99);

-- Okay transfer.
CALL transfer(UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), UUID('65f12b00-ac45-40fe-9f4e-16989522f8af'), 1000);

-- Reverse okay transfer.
CALL transfer(UUID('65f12b00-ac45-40fe-9f4e-16989522f8af'), UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), 1000);

-- Accounts are the same.
CALL transfer(UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), 1000);

-- Source account not existing.
CALL transfer(UUID('ffffffff-ffff-ffff-ffff-ffffffffffff'), UUID('65f12b00-ac45-40fe-9f4e-16989522f8af'), 1000);

-- Destination account not existing.
CALL transfer(UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), UUID('ffffffff-ffff-ffff-ffff-ffffffffffff'), 1000);

-- Underflow transfer.
CALL transfer(UUID('65f12b00-ac45-40fe-9f4e-16989522f8af'), UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), 1000);

-- Overflow transfer.
CALL transfer(UUID('9d0bfa29-b27e-4f93-93eb-f81e6eab2a41'), UUID('3c4f845f-f87f-4b77-afe7-5164a902b242'), 1000);
