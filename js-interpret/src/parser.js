const { op, fn, lt, xp, oo } = require('./token.js')
const { operations } = require('./operations.js')
const { functions } = require('./functions.js')
const debug = require('debug')
const log = debug('parser')

/**
 * Inserts brackets as per operator-precedence order.
 * Practically, a FORTRAN lexer implementation copy.
 *
 * @param {string} source - string of one expression.
 * @returns {string}
 */

function brackify (source) {
  const res = source.replace(/\s/g, '')
    .replace(/\(/g, '(((')
    .replace(/\)/g, ')))')
    .replace(/\+/g, '))+((')
    .replace(/-/g, '))-((')
    .replace(/\*/g, ')*(')
    .replace(/\//g, ')/(')
  return `(((${res})))`
}

/**
 * Separates preprocessed string to atomics level.
 *
 * @param {string} source - brackified expression.
 * @returns {string[]}
 */

function separate (source) {
  return source.replace(/,/g, ':')
    .replace(/\(/g, ':(:')
    .replace(/\)/g, ':):')
    .split(/:+/g)
    .slice(1, -1)
}

/**
 * Converts atom to appropriate token.
 *
 * @param {string} atom - string to create token from.
 * @returns {Token}
 */

function parseAtom (atom) {
  if (operations.hasOwnProperty(atom)) {
    log(`found OP of ${atom}`)
    return op(atom)
  }

  if (functions.hasOwnProperty(atom)) {
    log(`found FN of ${atom}`)
    return fn(atom)
  }

  let numRegExp = /\d+(\.\d+)?/
  if (atom.match(numRegExp)) {
    log(`found LT of ${atom}`)
    return lt(atom)
  }

  let objPathRegExp = /\w+(\.\w+)?/
  if (atom.match(objPathRegExp)) {
    log(`found OO of ${atom}`)
    return oo(atom.split(/\./g))
  }

  throw new Error(`Failed to parse atom value of '${atom}'`)
}

/**
 * Apply proper RPN ordering for expression.
 *
 * @param {Token[]} expr - source AST expression to order.
 * @returns {Token[]}
 */

function order (expr) {
  const res = []
  let opBuf, fnBuf

  for (const token of expr.reverse()) {
    switch (token.type) {
      case 'op':
        opBuf = token
        break
      case 'fn':
        fnBuf = token
        break
      default:
        res.push(token)
        if (opBuf) {
          res.push(opBuf)
          opBuf = null
        }
    }
  }

  if (fnBuf) {
    res.push(fnBuf)
  }

  return res
}

/**
 * Unwrap expression to be in flat form of stack RPN.
 *
 * @param {Token[]} expr - ordered non-flat RPN expr.
 * @returns {Token}
 */

function unwrap (expr) {
  if (expr.length === 1) {
    return expr[0]
  }

  return xp(order(expr))
}

/**
 * Process every string atom into computation token.
 *
 * @param {string[]} atoms - source atoms to build tokens from.
 * @returns {Token}
 */

function tokenize (atoms) {
  const expr = []

  while (atoms.length > 0) {
    const atom = atoms.shift()
    switch (atom) {
      case '(':
        expr.push(tokenize(atoms))
        break
      case ')':
        return unwrap(expr)
      default:
        expr.push(parseAtom(atom))
    }
  }

  return unwrap(expr)
}

/**
 * Simple build routine to flatten RPN expression.
 *
 * @param {Token} expr - non-flat expression to process.
 * @returns {Token[]}
 */

function normalize (expr) {
  let res = []

  for (const token of expr.value) {
    if (token.type === 'xp') {
      res = res.concat(normalize(token))
    } else {
      res.push(token)
    }
  }

  return res
}

/**
 * Wrapper to maintain interface simplicity.
 *
 * @param {string} strExpr - expression string to parse.
 * @returns {Token[]}
 */

function parseRpnStack (strExpr) {
  return normalize(tokenize(separate(brackify(strExpr))))
}

module.exports = { parseRpnStack }
