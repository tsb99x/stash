const debug = require('debug')
const log = debug('functions')

const functions = {
  'date' (ctx) {
    const y = ctx.pop()
    const m = ctx.pop()
    const d = ctx.pop()
    const res = new Date(y, m, d)
    log(`date of ${y}, ${m}, ${d}, res: ${res}`)
    return res.getTime()
  },
  'day' (ctx) {
    const d = ctx.pop()
    const res = 1000 * 60 * 60 * 24 * d
    log(`day of ${d}, res: ${res}`)
    return res
  }
}

module.exports = { functions }
