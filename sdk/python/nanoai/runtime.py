import ctypes
import os

def _resolve_lib_path(lib_path):
    candidates = [
        lib_path,
        os.environ.get("NANOAI_LIB_PATH"),
        os.path.join(os.path.dirname(__file__), "libnanoai.so"),
        os.path.join(os.path.dirname(__file__), "../../../build/libnanoai.so"),
    ]

    for candidate in candidates:
        if candidate and os.path.exists(candidate):
            return candidate

    return lib_path

class NanoRuntime:
    def __init__(self, lib_path="libnanoai.so"):
        self.lib_path = _resolve_lib_path(lib_path)
        self.lib = ctypes.CDLL(self.lib_path)

        self.lib.nanoai_create.restype = ctypes.c_void_p
        self.lib.nanoai_destroy.argtypes = [ctypes.c_void_p]

        self.lib.nanoai_string_free.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_string_free.restype = None

        self.lib.nanoai_load_model.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_load_model.restype = ctypes.c_bool

        self.lib.nanoai_generate.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int]
        self.lib.nanoai_generate.restype = ctypes.c_void_p

        # Swarm API
        self.lib.nanoai_run_swarm.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.POINTER(ctypes.c_char_p), ctypes.c_int, ctypes.c_char_p]
        self.lib.nanoai_run_swarm.restype = ctypes.c_void_p

        # Workflow API
        self.lib.nanoai_run_workflow.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_run_workflow.restype = ctypes.c_void_p

        # AI OS Layer
        self.lib.nanoai_os_boot.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_os_boot.restype = ctypes.c_bool
        self.lib.nanoai_os_dispatch.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.nanoai_os_dispatch.restype = ctypes.c_void_p

        self.lib.nanoai_get_runtime_telemetry.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_runtime_telemetry.restype = ctypes.c_void_p

        self.lib.nanoai_get_hardware_profile.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_hardware_profile.restype = ctypes.c_void_p

        self.lib.nanoai_get_cluster_nodes.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_cluster_nodes.restype = ctypes.c_void_p

        self.handle = self.lib.nanoai_create()
        if not self.handle:
            raise RuntimeError("nanoai_create failed")

    def _require_handle(self):
        if not self.handle:
            raise RuntimeError("NanoRuntime has been closed")

    def _decode_and_free(self, ptr):
        if not ptr:
            return ""
        b = ctypes.cast(ptr, ctypes.c_char_p).value
        s = b.decode() if b else ""
        self.lib.nanoai_string_free(ptr)
        return s

    def close(self):
        if getattr(self, "handle", None):
            self.lib.nanoai_destroy(self.handle)
            self.handle = None

    def destroy(self):
        self.close()

    def __enter__(self):
        self._require_handle()
        return self

    def __exit__(self, exc_type, exc, tb):
        self.close()
        return False

    def __del__(self):
        try:
            self.close()
        except Exception:
            pass

    def load_model(self, model_path, model_id):
        self._require_handle()
        return self.lib.nanoai_load_model(self.handle, model_path.encode(), model_id.encode())

    def generate(self, prompt, model_id, priority=2):
        self._require_handle()
        ptr = self.lib.nanoai_generate(self.handle, prompt.encode(), model_id.encode(), priority)
        return self._decode_and_free(ptr)

    def run_swarm(self, task_name, agents, input_data):
        self._require_handle()
        agent_ptrs = (ctypes.c_char_p * len(agents))(*[a.encode() for a in agents])
        ptr = self.lib.nanoai_run_swarm(self.handle, task_name.encode(), agent_ptrs, len(agents), input_data.encode())
        return self._decode_and_free(ptr)

    def run_workflow(self, workflow_json, input_data):
        self._require_handle()
        ptr = self.lib.nanoai_run_workflow(self.handle, workflow_json.encode(), input_data.encode())
        return self._decode_and_free(ptr)

    def boot_os(self):
        self._require_handle()
        return self.lib.nanoai_os_boot(self.handle)

    def os_dispatch(self, task):
        self._require_handle()
        ptr = self.lib.nanoai_os_dispatch(self.handle, task.encode())
        return self._decode_and_free(ptr)

    def get_runtime_telemetry(self):
        self._require_handle()
        ptr = self.lib.nanoai_get_runtime_telemetry(self.handle)
        return self._decode_and_free(ptr)

    def get_telemetry(self):
        return self.get_runtime_telemetry()

    def get_hardware_profile(self):
        self._require_handle()
        ptr = self.lib.nanoai_get_hardware_profile(self.handle)
        return self._decode_and_free(ptr)

    def get_cluster_nodes(self):
        self._require_handle()
        ptr = self.lib.nanoai_get_cluster_nodes(self.handle)
        return self._decode_and_free(ptr)
