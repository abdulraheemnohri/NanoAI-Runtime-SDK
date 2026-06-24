import ctypes
import os

class NanoRuntime:
    def __init__(self, lib_path="libnanoai.so"):
        self.lib = ctypes.CDLL(lib_path)

        self.lib.nanoai_create.restype = ctypes.c_void_p
        self.lib.nanoai_destroy.argtypes = [ctypes.c_void_p]

        self.lib.nanoai_load_model.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_load_model.restype = ctypes.c_bool

        self.lib.nanoai_generate.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int]
        self.lib.nanoai_generate.restype = ctypes.c_char_p

        self.lib.nanoai_get_runtime_telemetry.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_runtime_telemetry.restype = ctypes.c_char_p

        self.lib.nanoai_get_hardware_profile.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_hardware_profile.restype = ctypes.c_char_p

        self.lib.nanoai_get_cluster_nodes.argtypes = [ctypes.c_void_p]
        self.lib.nanoai_get_cluster_nodes.restype = ctypes.c_char_p

        self.handle = self.lib.nanoai_create()

    def __del__(self):
        if hasattr(self, 'handle'):
            self.lib.nanoai_destroy(self.handle)

    def load_model(self, model_path, model_id):
        return self.lib.nanoai_load_model(self.handle, model_path.encode(), model_id.encode())

    def generate(self, prompt, model_id, priority=2):
        res = self.lib.nanoai_generate(self.handle, prompt.encode(), model_id.encode(), priority)
        return res.decode()

    def get_telemetry(self):
        res = self.lib.nanoai_get_runtime_telemetry(self.handle)
        return res.decode()

    def get_hardware_profile(self):
        res = self.lib.nanoai_get_hardware_profile(self.handle)
        return res.decode()

    def get_cluster_nodes(self):
        res = self.lib.nanoai_get_cluster_nodes(self.handle)
        return res.decode()
