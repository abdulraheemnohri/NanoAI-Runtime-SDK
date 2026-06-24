const ffi = require('ffi-napi');
const ref = require('ref-napi');
const ArrayType = require('ref-array-di')(ref);
const path = require('path');
const fs = require('fs');

const CharPtr = ref.types.CString;
const CharPtrArray = ArrayType(CharPtr);

function resolveLibPath() {
  const candidates = [
    process.env.NANOAI_LIB_PATH,
    path.join(__dirname, 'libnanoai.so'),
    path.join(__dirname, '..', '..', 'build', 'libnanoai.so'),
    path.join(process.cwd(), 'libnanoai.so')
  ].filter(Boolean);

  for (const p of candidates) {
    if (fs.existsSync(p)) return p;
  }

  return path.join(__dirname, 'libnanoai.so');
}

const libPath = resolveLibPath();

const nanoai = ffi.Library(libPath, {
  'nanoai_create': ['pointer', []],
  'nanoai_destroy': ['void', ['pointer']],
  'nanoai_load_model': ['bool', ['pointer', 'string', 'string']],
  'nanoai_generate': ['string', ['pointer', 'string', 'string', 'int']],
  'nanoai_run_swarm': ['string', ['pointer', 'string', 'pointer', 'int', 'string']],
  'nanoai_run_workflow': ['string', ['pointer', 'string', 'string']],
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

  runSwarm(taskName, agents, inputData) {
    const agentArray = new CharPtrArray(agents);
    return nanoai.nanoai_run_swarm(this.handle, taskName, agentArray, agents.length, inputData);
  }

  runWorkflow(workflowJson, inputData) {
    return nanoai.nanoai_run_workflow(this.handle, workflowJson, inputData);
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
