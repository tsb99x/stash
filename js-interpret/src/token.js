/**
 * @typedef Token
 * @type {object}
 * @property {string} type - type of token.
 * @property {string | string[] | Token[]} value - literal representation or tokens set.
 */

/**
 * Operator token constructor.
 *
 * @param {string} value - literal representation of op.
 * @returns {Token}
 */

function op (value) {
  return { type: 'op', value }
}

/**
 * Function token constructor.
 *
 * @param {string} value - literal representation of op.
 * @returns {Token}
 */

function fn (value) {
  return { type: 'fn', value }
}

/**
 * Literal token constructor.
 *
 * @param {string} value - contents of literal.
 * @returns {Token}
 */

function lt (value) {
  return { type: 'lt', value }
}

/**
 * Expression token constructor.
 * Used only in parsing stage, not in execution.
 *
 * @param {Token[]} value - expression tokens.
 * @returns {Token}
 */

function xp (value) {
  return { type: 'xp', value }
}

/**
 * Object path token constructor.
 *
 * @param {string[]} value - path of object to retrieve.
 * @returns {Token}
 */

function oo (value) {
  return { type: 'oo', value }
}

module.exports = { op, fn, lt, xp, oo }
