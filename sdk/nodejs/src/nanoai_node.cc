#include <node_api.h>
#include <string>
#include <vector>
#include "nanoai/runtime.h"

struct NanoRuntimeWrap {
  nanoai_runtime_t handle;
};

static void finalize_runtime(napi_env env, void* data, void* hint) {
  auto* w = static_cast<NanoRuntimeWrap*>(data);
  if (w && w->handle) nanoai_destroy(w->handle);
  delete w;
}

static bool get_utf8(napi_env env, napi_value v, std::string& out) {
  size_t len = 0;
  if (napi_get_value_string_utf8(env, v, nullptr, 0, &len) != napi_ok) return false;
  std::string buf(len + 1, '\0');
  if (napi_get_value_string_utf8(env, v, buf.data(), len + 1, &len) != napi_ok) return false;
  out = std::string(buf.data(), len);
  return true;
}

static napi_value make_string(napi_env env, const char* s) {
  napi_value out;
  if (!s) { napi_get_undefined(env, &out); return out; }
  napi_create_string_utf8(env, s, NAPI_AUTO_LENGTH, &out);
  return out;
}

static NanoRuntimeWrap* unwrap_runtime(napi_env env, napi_callback_info info, napi_value* this_arg_out) {
  size_t argc = 0; napi_value this_arg;
  if (napi_get_cb_info(env, info, &argc, nullptr, &this_arg, nullptr) != napi_ok) return nullptr;
  NanoRuntimeWrap* w = nullptr;
  if (napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w)) != napi_ok) return nullptr;
  if (this_arg_out) *this_arg_out = this_arg;
  return w;
}

static napi_value rt_ctor(napi_env env, napi_callback_info info) {
  napi_value this_arg; size_t argc = 0;
  if (napi_get_cb_info(env, info, &argc, nullptr, &this_arg, nullptr) != napi_ok) return nullptr;
  auto* w = new NanoRuntimeWrap();
  w->handle = nanoai_create();
  napi_wrap(env, this_arg, w, finalize_runtime, nullptr, nullptr);
  return this_arg;
}

static napi_value rt_load_model(napi_env env, napi_callback_info info) {
  size_t argc = 2; napi_value argv[2]; napi_value this_arg;
  napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr);
  NanoRuntimeWrap* w = nullptr; napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w));
  std::string p, id; get_utf8(env, argv[0], p); get_utf8(env, argv[1], id);
  bool ok = nanoai_load_model(w->handle, p.c_str(), id.c_str());
  napi_value out; napi_get_boolean(env, ok, &out);
  return out;
}

static napi_value rt_generate(napi_env env, napi_callback_info info) {
  size_t argc = 3; napi_value argv[3]; napi_value this_arg;
  napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr);
  NanoRuntimeWrap* w = nullptr; napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w));
  std::string p, id; get_utf8(env, argv[0], p); get_utf8(env, argv[1], id);
  int32_t prio = 2; if (argc >= 3) napi_get_value_int32(env, argv[2], &prio);
  char* res = nanoai_generate(w->handle, p.c_str(), id.c_str(), prio);
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value rt_get_registered_agents(napi_env env, napi_callback_info info) {
    napi_value this_arg; NanoRuntimeWrap* w = unwrap_runtime(env, info, &this_arg);
    char* res = nanoai_get_registered_agents(w->handle);
    napi_value out = make_string(env, res); nanoai_string_free(res);
    return out;
}

static napi_value rt_get_cluster_health(napi_env env, napi_callback_info info) {
    napi_value this_arg; NanoRuntimeWrap* w = unwrap_runtime(env, info, &this_arg);
    char* res = nanoai_get_cluster_health(w->handle);
    napi_value out = make_string(env, res); nanoai_string_free(res);
    return out;
}

static napi_value rt_set_eco_mode(napi_env env, napi_callback_info info) {
    size_t argc = 1; napi_value argv[1]; napi_value this_arg;
    napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr);
    NanoRuntimeWrap* w = nullptr; napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w));
    bool enabled; napi_get_value_bool(env, argv[0], &enabled);
    nanoai_set_eco_mode(w->handle, enabled);
    napi_value undef; napi_get_undefined(env, &undef);
    return undef;
}

static napi_value rt_run_swarm(napi_env env, napi_callback_info info) {
  size_t argc = 3; napi_value argv[3]; napi_value this_arg;
  napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr);
  NanoRuntimeWrap* w = nullptr; napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w));
  std::string task, input; get_utf8(env, argv[0], task); get_utf8(env, argv[2], input);
  uint32_t len = 0; napi_get_array_length(env, argv[1], &len);
  std::vector<std::string> agents(len); std::vector<const char*> ptrs(len);
  for (uint32_t i=0; i<len; ++i) { napi_value v; napi_get_element(env, argv[1], i, &v); get_utf8(env, v, agents[i]); ptrs[i] = agents[i].c_str(); }
  char* res = nanoai_run_swarm(w->handle, task.c_str(), ptrs.data(), (int)len, input.c_str());
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value rt_run_workflow(napi_env env, napi_callback_info info) {
  size_t argc = 2; napi_value argv[2]; napi_value this_arg;
  napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr);
  NanoRuntimeWrap* w = nullptr; napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w));
  std::string json, input; get_utf8(env, argv[0], json); get_utf8(env, argv[1], input);
  char* res = nanoai_run_workflow(w->handle, json.c_str(), input.c_str());
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value rt_boot_os(napi_env env, napi_callback_info info) {
  napi_value this_arg; NanoRuntimeWrap* w = unwrap_runtime(env, info, &this_arg);
  bool ok = nanoai_os_boot(w->handle);
  napi_value out; napi_get_boolean(env, ok, &out);
  return out;
}

static napi_value rt_os_dispatch(napi_env env, napi_callback_info info) {
  size_t argc = 1; napi_value argv[1]; napi_value this_arg;
  napi_get_cb_info(env, info, &argc, argv, &this_arg, nullptr);
  NanoRuntimeWrap* w = nullptr; napi_unwrap(env, this_arg, reinterpret_cast<void**>(&w));
  std::string task; get_utf8(env, argv[0], task);
  char* res = nanoai_os_dispatch(w->handle, task.c_str());
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value rt_get_telemetry(napi_env env, napi_callback_info info) {
  napi_value this_arg; NanoRuntimeWrap* w = unwrap_runtime(env, info, &this_arg);
  char* res = nanoai_get_runtime_telemetry(w->handle);
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value rt_get_hardware_profile(napi_env env, napi_callback_info info) {
  napi_value this_arg; NanoRuntimeWrap* w = unwrap_runtime(env, info, &this_arg);
  char* res = nanoai_get_hardware_profile(w->handle);
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value rt_get_cluster_nodes(napi_env env, napi_callback_info info) {
  napi_value this_arg; NanoRuntimeWrap* w = unwrap_runtime(env, info, &this_arg);
  char* res = nanoai_get_cluster_nodes(w->handle);
  napi_value out = make_string(env, res); nanoai_string_free(res);
  return out;
}

static napi_value init(napi_env env, napi_value exports) {
  napi_property_descriptor props[] = {
      {"loadModel", 0, rt_load_model, 0, 0, 0, napi_default, 0},
      {"generate", 0, rt_generate, 0, 0, 0, napi_default, 0},
      {"runSwarm", 0, rt_run_swarm, 0, 0, 0, napi_default, 0},
      {"runWorkflow", 0, rt_run_workflow, 0, 0, 0, napi_default, 0},
      {"bootOS", 0, rt_boot_os, 0, 0, 0, napi_default, 0},
      {"osDispatch", 0, rt_os_dispatch, 0, 0, 0, napi_default, 0},
      {"getTelemetry", 0, rt_get_telemetry, 0, 0, 0, napi_default, 0},
      {"getHardwareProfile", 0, rt_get_hardware_profile, 0, 0, 0, napi_default, 0},
      {"getClusterNodes", 0, rt_get_cluster_nodes, 0, 0, 0, napi_default, 0},
      {"getRegisteredAgents", 0, rt_get_registered_agents, 0, 0, 0, napi_default, 0},
      {"getClusterHealth", 0, rt_get_cluster_health, 0, 0, 0, napi_default, 0},
      {"setEcoMode", 0, rt_set_eco_mode, 0, 0, 0, napi_default, 0},
  };
  napi_value ctor;
  napi_define_class(env, "NanoRuntime", NAPI_AUTO_LENGTH, rt_ctor, nullptr, sizeof(props)/sizeof(props[0]), props, &ctor);
  napi_set_named_property(env, exports, "NanoRuntime", ctor);
  return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
