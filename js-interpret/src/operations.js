const debug = require('debug')
const log = debug('operations')

/**
 * Dictionary of all available operations to execute in program.
 */

const operations = {
  '+' (a, b) {
    let res = Number(a) + Number(b)
    log(`add of ${a}, ${b}, res: ${res}`)
    return res
  }
}

module.exports = { operations }
