const { operations } = require('./operations.js')
const { functions } = require('./functions.js')
const debug = require('debug')
const log = debug('executor')

/**
 * Process token stack and return a literal result.
 *
 * @param {object} dataset - dataset to apply expression to.
 * @param {Token[]} stack - concrete expression from formulae.
 * @returns {Date}
 */

function executeRpnStack (dataset, stack) {
  const ctx = []
  let token

  while (stack.length > 0) {
    token = stack.shift()
    switch (token.type) {
      case 'lt':
        ctx.push(token.value)
        break
      case 'op':
        ctx.push(executeOperation(token.value, ctx))
        break
      case 'fn':
        ctx.push(executeFunction(token.value, ctx))
        break
      case 'oo':
        ctx.push(evaluateObjectProperty(dataset, token.value))
        break
      default:
        throw new Error(`Failed to process token of type ${token.type}`)
    }
  }

  if (ctx.length <= 0) {
    throw new Error(`Failed to retrieve result from CTX, as it is empty`)
  }

  if (ctx.length > 1) {
    throw new Error(`Failed to retrieve result from CTX, as it have multiple elements '${ctx}'`)
  }

  log(`expression result of ${ctx[0]}`)

  return new Date(ctx[0])
}

/**
 * Execute given operation in given context.
 *
 * @param {string} name - name of operation to invoke.
 * @param {object[]} ctx - context to get arguments from.
 * @returns {object}
 */

function executeOperation (name, ctx) {
  if (!operations.hasOwnProperty(name)) {
    throw new Error(`Failed to find operation with name of ${name}`)
  }

  log(`invoking op of ${name} with ${ctx}`)
  const res = operations[name](ctx.pop(), ctx.pop())

  if (res == null) {
    throw new Error(`Failed to process operation of ${name}, left with CTX of ${ctx}`)
  }

  return res
}

/**
 * Retrieves data from path of dataset.path.part.
 * In fact, a validator for simplified JSON path of props.
 *
 * @param {object} dataset - dataset to validate path against.
 * @param {string} path - array of path parts.
 * @returns {object}
 */

function evaluateObjectProperty (dataset, path) {
  let subObject = dataset
  let part

  for (part of path) {
    subObject = subObject[part]
    if (subObject == null) {
      throw new Error(`Failed to acquire path of '${path}' on object of '${JSON.stringify(dataset, null, 4)}'`)
    }
  }

  return subObject
}

/**
 * Executes given function in given context.
 *
 * @param {string} name - name of function to invoke.
 * @param {object[]} ctx - context, to get arguments from.
 * @returns {object}
 */

function executeFunction (name, ctx) {
  if (!functions.hasOwnProperty(name)) {
    throw new Error(`Failed to find function with name of "${name}"`)
  }

  const res = functions[name](ctx)

  if (res == null) {
    throw new Error(`Failed to process function of ${name}, left with CTX of ${ctx}`)
  }

  return res
}

module.exports = { executeRpnStack }
