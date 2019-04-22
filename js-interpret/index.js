const { parseRpnStack } = require('./src/parser.js')
const { executeRpnStack } = require('./src/executor.js')

const dataset = {
  'a': {
    'b': {
      'c': +new Date()
    }
  }
}

const srcFormulae = 'a.b.c + day(5.0)'
const rpnStack = parseRpnStack(srcFormulae)
const result = executeRpnStack(dataset, rpnStack)

console.log(`Result date of: ${result}`)
