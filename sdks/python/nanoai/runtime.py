import ctypes
import os

class NanoRuntime:
    def __init__(self, lib_path="libnanoai.so"):
        self.lib = ctypes.CDLL(lib_path)

        self.lib.nanoai_create.restype = ctypes.c_void_p
        self.lib.nanoai_destroy.argtypes = [ctypes.c_void_p]

        self.lib.nanoai_load_model_id.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_load_model_id.restype = ctypes.c_bool

        self.lib.nanoai_generate_id.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_generate_id.restype = ctypes.c_char_p

        self.lib.nanoai_get_detected_hardware.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.nanoai_get_detected_hardware.restype = ctypes.c_char_p

        self.lib.nanoai_convert_model.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int]
        self.lib.nanoai_convert_model.restype = ctypes.c_bool

        self.handle = self.lib.nanoai_create()

    def __del__(self):
        if hasattr(self, 'handle'):
            self.lib.nanoai_destroy(self.handle)

    def load_model(self, model_path, model_id="default"):
        return self.lib.nanoai_load_model_id(self.handle, model_path.encode(), model_id.encode())

    def generate(self, prompt, model_id="default"):
        res = self.lib.nanoai_generate_id(self.handle, prompt.encode(), model_id.encode())
        return res.decode()

    def get_detected_hardware(self, model_id="default"):
        res = self.lib.nanoai_get_detected_hardware(self.handle, model_id.encode())
        return res.decode()

    @staticmethod
    def convert_model(input_path, output_path, quantization_type, lib_path="libnanoai.so"):
        lib = ctypes.CDLL(lib_path)
        return lib.nanoai_convert_model(input_path.encode(), output_path.encode(), quantization_type)
