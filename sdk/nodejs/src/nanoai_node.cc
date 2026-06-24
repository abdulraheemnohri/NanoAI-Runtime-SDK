#include <node_api.h>
#include <string>
#include <vector>
#include "nanoai/runtime.h"

struct NanoRuntimeWrap {
  nanoai_runtime_t handle;
};

static void finalize_runtime(napi_env env, void* data, void* hint) {
  (void)env;
  (void)hint;
  auto* w = static_cast<NanoRuntimeWrap*>(data);
  if (!w) return;
  if (w->handle) nanoai_destroy(w->handle);
  delete w;
}

static bool get_utf8(napi_env env, napi_value v, std::string& out) {
  size_t len = 0;
  if (napi_get_value_string_utf8(env, v, nullptr, 0, &len) != napi_ok) return false;
  std::string buf(len, '\0');
  if (napi_get_value_string_utf8(env, v, buf.data(), len + 1, &len) != napi_ok) return false;
  out = std::move(buf);
  return true;
}

static napi_value make_string(napi_env env, const char* s) {
  napi_value out;
  if (!s) {
    napi_get_undefined(env, &out);
    return out;
  }
  napi_create_string_utf8(env, s, NAPI_AUTO_LENGTH, &out);
  return out;
}

static NanoRuntimeWrap* unwrap_runtime(napi_env env, napi_callback_info info, napi_value* this_arg_out) {
  size_t argc = 0;
  napi_value this_arg;
  if (napi_get_cb_info(env, info, &argc, nullptr, &this_arg, nullptr) != napi_ok) return nullptr;
  NanoRuntimeWrap* w = nullptr;
  if (napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w)) != napi_ok) return nullptr;
  if (this_arg_out) *this_arg_out = this_arg;
  return w;
}

static napi_value rt_ctor(napi_env env, napi_callback_info info) {
  napi_value this_arg;
  size_t argc = 0;
  if (napi_get_cb_info(env, info, &argc, nullptr, &this_arg, nullptr) != napi_ok) return nullptr;

  auto* w = new NanoRuntimeWrap();
  w->handle = nanoai_create();
  if (!w->handle) {
    delete w;
    napi_throw_error(env, nullptr, "nanoai_create failed");
    return nullptr;
  }

  if (napi_wrap(env, this_arg, w, finalize_runtime, nullptr, nullptr) != napi_ok) {
    nanoai_destroy(w->handle);
    delete w;
    napi_throw_error(env, nullptr, "napi_wrap failed");
    return nullptr;
  }

  return this_arg;
}

static napi_value rt_destroy(napi_env env, napi_callback_info info) {
  napi_value this_arg;
  auto* w = unwrap_runtime(env, info, &this_arg);
  if (!w) return nullptr;
  if (w->handle) {
    nanoai_destroy(w->handle);
    w->handle = nullptr;
  }
  napi_value undef;
  napi_get_undefined(env, &undef);
  return undef;
}

static napi_value rt_load_model(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_value this_arg;
  if (napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr) != napi_ok) return nullptr;
  if (argc < 2) {
    napi_throw_type_error(env, nullptr, "loadModel(modelPath, modelId) expected 2 args");
    return nullptr;
  }

  NanoRuntimeWrap* w = nullptr;
  if (napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w)) != napi_ok || !w || !w->handle) return nullptr;

  std::string model_path;
  std::string model_id;
  if (!get_utf8(env, argv[0], model_path) || !get_utf8(env, argv[1], model_id)) {
    napi_throw_type_error(env, nullptr, "loadModel expects (string, string)");
    return nullptr;
  }

  bool ok = nanoai_load_model(w->handle, model_path.c_str(), model_id.c_str());
  napi_value out;
  napi_get_boolean(env, ok, &out);
  return out;
}

static napi_value rt_generate(napi_env env, napi_callback_info info) {
  size_t argc = 3;
  napi_value argv[3];
  napi_value this_arg;
  if (napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr) != napi_ok) return nullptr;
  if (argc < 2) {
    napi_throw_type_error(env, nullptr, "generate(prompt, modelId, priority?) expected 2-3 args");
    return nullptr;
  }

  NanoRuntimeWrap* w = nullptr;
  if (napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w)) != napi_ok || !w || !w->handle) return nullptr;

  std::string prompt;
  std::string model_id;
  if (!get_utf8(env, argv[0], prompt) || !get_utf8(env, argv[1], model_id)) {
    napi_throw_type_error(env, nullptr, "generate expects (string, string, number?)");
    return nullptr;
  }

  int32_t priority = 2;
  if (argc >= 3) {
    if (napi_get_value_int32(env, argv[2], &priority) != napi_ok) {
      napi_throw_type_error(env, nullptr, "priority must be a number");
      return nullptr;
    }
  }

  char* res = nanoai_generate(w->handle, prompt.c_str(), model_id.c_str(), priority);
  napi_value out = make_string(env, res);
  nanoai_string_free(res);
  return out;
}

static napi_value rt_run_swarm(napi_env env, napi_callback_info info) {
  size_t argc = 3;
  napi_value argv[3];
  napi_value this_arg;
  if (napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr) != napi_ok) return nullptr;
  if (argc < 3) {
    napi_throw_type_error(env, nullptr, "runSwarm(taskName, agents, input) expected 3 args");
    return nullptr;
  }

  NanoRuntimeWrap* w = nullptr;
  if (napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w)) != napi_ok || !w || !w->handle) return nullptr;

  std::string task_name;
  std::string input;
  if (!get_utf8(env, argv[0], task_name) || !get_utf8(env, argv[2], input)) {
    napi_throw_type_error(env, nullptr, "runSwarm expects (string, string[], string)");
    return nullptr;
  }

  bool is_array = false;
  if (napi_is_array(env, argv[1], &is_array) != napi_ok || !is_array) {
    napi_throw_type_error(env, nullptr, "agents must be an array");
    return nullptr;
  }

  uint32_t len = 0;
  if (napi_get_array_length(env, argv[1], &len) != napi_ok) return nullptr;

  std::vector<std::string> agent_strs;
  agent_strs.reserve(len);
  std::vector<const char*> agent_ptrs;
  agent_ptrs.reserve(len);

  for (uint32_t i = 0; i < len; ++i) {
    napi_value v;
    if (napi_get_element(env, argv[1], i, &v) != napi_ok) return nullptr;
    std::string s;
    if (!get_utf8(env, v, s)) {
      napi_throw_type_error(env, nullptr, "agents array must contain strings");
      return nullptr;
    }
    agent_strs.emplace_back(std::move(s));
    agent_ptrs.push_back(agent_strs.back().c_str());
  }

  char* res = nanoai_run_swarm(w->handle, task_name.c_str(), agent_ptrs.data(), static_cast<int>(agent_ptrs.size()), input.c_str());
  napi_value out = make_string(env, res);
  nanoai_string_free(res);
  return out;
}

static napi_value rt_run_workflow(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_value this_arg;
  if (napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr) != napi_ok) return nullptr;
  if (argc < 2) {
    napi_throw_type_error(env, nullptr, "runWorkflow(workflowJson, input) expected 2 args");
    return nullptr;
  }

  NanoRuntimeWrap* w = nullptr;
  if (napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w)) != napi_ok || !w || !w->handle) return nullptr;

  std::string workflow_json;
  std::string input;
  if (!get_utf8(env, argv[0], workflow_json) || !get_utf8(env, argv[1], input)) {
    napi_throw_type_error(env, nullptr, "runWorkflow expects (string, string)");
    return nullptr;
  }

  char* res = nanoai_run_workflow(w->handle, workflow_json.c_str(), input.c_str());
  napi_value out = make_string(env, res);
  nanoai_string_free(res);
  return out;
}

static napi_value rt_get_telemetry(napi_env env, napi_callback_info info) {
  napi_value this_arg;
  auto* w = unwrap_runtime(env, info, &this_arg);
  if (!w || !w->handle) return nullptr;
  char* res = nanoai_get_runtime_telemetry(w->handle);
  napi_value out = make_string(env, res);
  nanoai_string_free(res);
  return out;
}

static napi_value rt_get_hardware_profile(napi_env env, napi_callback_info info) {
  napi_value this_arg;
  auto* w = unwrap_runtime(env, info, &this_arg);
  if (!w || !w->handle) return nullptr;
  char* res = nanoai_get_hardware_profile(w->handle);
  napi_value out = make_string(env, res);
  nanoai_string_free(res);
  return out;
}

static napi_value rt_get_cluster_nodes(napi_env env, napi_callback_info info) {
  napi_value this_arg;
  auto* w = unwrap_runtime(env, info, &this_arg);
  if (!w || !w->handle) return nullptr;
  char* res = nanoai_get_cluster_nodes(w->handle);
  napi_value out = make_string(env, res);
  nanoai_string_free(res);
  return out;
}

static napi_value init(napi_env env, napi_value exports) {
  napi_property_descriptor props[] = {
      {"destroy", 0, rt_destroy, 0, 0, 0, napi_default, 0},
      {"loadModel", 0, rt_load_model, 0, 0, 0, napi_default, 0},
      {"generate", 0, rt_generate, 0, 0, 0, napi_default, 0},
      {"runSwarm", 0, rt_run_swarm, 0, 0, 0, napi_default, 0},
      {"runWorkflow", 0, rt_run_workflow, 0, 0, 0, napi_default, 0},
      {"getTelemetry", 0, rt_get_telemetry, 0, 0, 0, napi_default, 0},
      {"getHardwareProfile", 0, rt_get_hardware_profile, 0, 0, 0, napi_default, 0},
      {"getClusterNodes", 0, rt_get_cluster_nodes, 0, 0, 0, napi_default, 0},
  };

  napi_value ctor;
  if (napi_define_class(env, "NanoRuntime", NAPI_AUTO_LENGTH, rt_ctor, nullptr,
                        sizeof(props) / sizeof(props[0]), props, &ctor) != napi_ok) {
    napi_throw_error(env, nullptr, "napi_define_class failed");
    return nullptr;
  }

  napi_set_named_property(env, exports, "NanoRuntime", ctor);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
