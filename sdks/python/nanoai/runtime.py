import ctypes
import os
import platform

class NanoRuntime:
    def __init__(self, lib_path=None):
        if lib_path is None:
            # Attempt to find libnanoai
            system = platform.system()
            if system == "Linux":
                lib_name = "libnanoai.so"
            elif system == "Darwin":
                lib_name = "libnanoai.dylib"
            elif system == "Windows":
                lib_name = "nanoai.dll"
            else:
                raise RuntimeError(f"Unsupported platform: {system}")

            lib_path = lib_name

        try:
            self.lib = ctypes.CDLL(lib_path)
        except OSError:
            # Fallback to local search if not in system path
            local_lib = os.path.join(os.getcwd(), lib_path)
            if os.path.exists(local_lib):
                self.lib = ctypes.CDLL(local_lib)
            else:
                raise RuntimeError(f"Could not load {lib_path}. Please ensure it is in your library path.")

        # Define argtypes and restypes
        self.lib.nanoai_create.restype = ctypes.c_void_p
        self.lib.nanoai_destroy.argtypes = [ctypes.c_void_p]

        self.lib.nanoai_load_model.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.nanoai_load_model.restype = ctypes.c_bool

        self.lib.nanoai_generate.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.nanoai_generate.restype = ctypes.c_char_p

        # Since our C++ uses a class, we need a C-compatible wrapper or
        # expose C functions from the library. Let's update the C++ core
        # to expose a C API for Python/Rust.
        self.handle = self.lib.nanoai_create()

    def __del__(self):
        if hasattr(self, 'handle') and self.handle:
            self.lib.nanoai_destroy(self.handle)

    def load_model(self, model_path: str) -> bool:
        return self.lib.nanoai_load_model(self.handle, model_path.encode('utf-8'))

    def generate(self, prompt: str) -> str:
        result = self.lib.nanoai_generate(self.handle, prompt.encode('utf-8'))
        return result.decode('utf-8')
