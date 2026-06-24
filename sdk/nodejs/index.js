const ffi = require('ffi-napi');
const path = require('path');

const libPath = path.join(__dirname, 'libnanoai.so');

const nanoai = ffi.Library(libPath, {
  'nanoai_create': ['pointer', []],
  'nanoai_destroy': ['void', ['pointer']],
  'nanoai_load_model': ['bool', ['pointer', 'string', 'string']],
  'nanoai_generate': ['string', ['pointer', 'string', 'string', 'int']],
  'nanoai_get_runtime_telemetry': ['string', ['pointer']],
  'nanoai_get_hardware_profile': ['string', ['pointer']],
  'nanoai_get_cluster_nodes': ['string', ['pointer']]
});

class NanoRuntime {
  constructor() {
    this.handle = nanoai.nanoai_create();
  }

  destroy() {
    if (this.handle) {
      nanoai.nanoai_destroy(this.handle);
      this.handle = null;
    }
  }

  loadModel(modelPath, modelId) {
    return nanoai.nanoai_load_model(this.handle, modelPath, modelId);
  }

  generate(prompt, modelId, priority = 2) {
    return nanoai.nanoai_generate(this.handle, prompt, modelId, priority);
  }

  getTelemetry() {
    return nanoai.nanoai_get_runtime_telemetry(this.handle);
  }

  getHardwareProfile() {
    return nanoai.nanoai_get_hardware_profile(this.handle);
  }

  getClusterNodes() {
    return nanoai.nanoai_get_cluster_nodes(this.handle);
  }
}

module.exports = { NanoRuntime };
