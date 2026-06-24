const path = require('path');
const bindingPath = path.join(__dirname, 'build', 'Release', 'nanoai.node');

try {
  module.exports = require(bindingPath);
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
