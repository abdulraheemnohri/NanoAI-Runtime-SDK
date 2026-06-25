import ctypes
import os
import json

class NanoRuntime:
    def __init__(self, lib_path="libnanoai.so"):
        if not os.path.exists(lib_path):
            alt_path = os.path.join(os.path.dirname(__file__), "../../../build/libnanoai.so")
            if os.path.exists(alt_path):
                lib_path = alt_path

        self.lib = ctypes.CDLL(lib_path)

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

        # Telemetry & Discovery
        self.lib.nanoai_get_runtime_telemetry.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_runtime_telemetry.restype = ctypes.c_void_p

        self.lib.nanoai_get_hardware_profile.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_hardware_profile.restype = ctypes.c_void_p

        self.lib.nanoai_get_cluster_nodes.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_cluster_nodes.restype = ctypes.c_void_p

        # NRX Refinements
        self.lib.nanoai_get_registered_agents.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_registered_agents.restype = ctypes.c_void_p

        self.lib.nanoai_get_cluster_health.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_cluster_health.restype = ctypes.c_void_p

        self.lib.nanoai_set_eco_mode.argtypes = [ctypes.c_void_p, ctypes.c_bool]
        self.lib.nanoai_set_eco_mode.restype = None

        self.handle = self.lib.nanoai_create()

    def _decode_and_free(self, ptr):
        if not ptr:
            return ""
        b = ctypes.cast(ptr, ctypes.c_char_p).value
        s = b.decode() if b else ""
        self.lib.nanoai_string_free(ptr)
        return s

    def __del__(self):
        if hasattr(self, 'handle') and self.handle:
            self.lib.nanoai_destroy(self.handle)
            self.handle = None

    def load_model(self, model_path, model_id):
        return self.lib.nanoai_load_model(self.handle, model_path.encode(), model_id.encode())

    def generate(self, prompt, model_id, priority=2):
        ptr = self.lib.nanoai_generate(self.handle, prompt.encode(), model_id.encode(), priority)
        return self._decode_and_free(ptr)

    def run_swarm(self, task_name, agents, input_data):
        agent_ptrs = (ctypes.c_char_p * len(agents))(*[a.encode() for a in agents])
        ptr = self.lib.nanoai_run_swarm(self.handle, task_name.encode(), agent_ptrs, len(agents), input_data.encode())
        return self._decode_and_free(ptr)

    def run_workflow(self, workflow_json, input_data):
        if isinstance(workflow_json, dict):
            workflow_json = json.dumps(workflow_json)
        ptr = self.lib.nanoai_run_workflow(self.handle, workflow_json.encode(), input_data.encode())
        return self._decode_and_free(ptr)

    def boot_os(self):
        return self.lib.nanoai_os_boot(self.handle)

    def os_dispatch(self, task):
        ptr = self.lib.nanoai_os_dispatch(self.handle, task.encode())
        return self._decode_and_free(ptr)

    def get_telemetry(self):
        ptr = self.lib.nanoai_get_runtime_telemetry(self.handle)
        return self._decode_and_free(ptr)

    def get_hardware_profile(self):
        ptr = self.lib.nanoai_get_hardware_profile(self.handle)
        return self._decode_and_free(ptr)

    def get_cluster_nodes(self):
        ptr = self.lib.nanoai_get_cluster_nodes(self.handle)
        return self._decode_and_free(ptr)

    def get_registered_agents(self):
        ptr = self.lib.nanoai_get_registered_agents(self.handle)
        s = self._decode_and_free(ptr)
        return s.split(",") if s else []

    def get_cluster_health(self):
        ptr = self.lib.nanoai_get_cluster_health(self.handle)
        return json.loads(self._decode_and_free(ptr))

    def set_eco_mode(self, enabled):
        self.lib.nanoai_set_eco_mode(self.handle, enabled)
