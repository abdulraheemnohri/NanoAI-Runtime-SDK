const path = require('path');
const bindingPath = path.join(__dirname, 'build', 'Release', 'nanoai.node');

try {
  const addon = require(bindingPath);

  // High-level wrapper for NRX
  class NanoRuntime extends addon.NanoRuntime {
    constructor() {
      super();
    }

    runWorkflow(json, input) {
      const jsonStr = typeof json === 'object' ? JSON.stringify(json) : json;
      return super.runWorkflow(jsonStr, input);
    }
  }

  module.exports = { NanoRuntime };
} catch (e) {
  const msg = [
    'Failed to load NanoAI Node addon.',
    `Tried: ${bindingPath}`,
    'Build it with: npm install (from sdk/nodejs)',
    'Make sure libnanoai.so is built in ../../build (cmake -S . -B build && cmake --build build).',
    `Original error: ${e && e.message ? e.message : String(e)}`
  ].join('\n');
  throw new Error(msg);
}
