const readline = require('readline')

/**
 * Prompts user input.
 *
 * @param rl {Interface} -- readline interface to use.
 * @param msg {string} -- invite message to prompt user input.
 * @param separator {string} -- characters to separate invite from input.
 * @returns {Promise<string>}
 */

function prompt(rl, msg, separator = ' > ') {
    return new Promise(resolve => {
        rl.question(msg + separator, resolve)
    })
}

(async function main() {
    try {
        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout
        })

        const name = await prompt(rl, 'Input name')
        const years = await prompt(rl, 'Input years')
        const username = await prompt(rl, 'Input username')

        console.log(`your name is '${name}', you are '${years}' years old, and your username is '${username}'`)

        rl.close()
    } catch (e) {
        console.error(e)
    }
})()
