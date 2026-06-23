import ctypes
import os
import platform

class NanoRuntime:
    def __init__(self, lib_path=None):
        if lib_path is None:
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
            local_lib = os.path.join(os.getcwd(), lib_path)
            if os.path.exists(local_lib):
                self.lib = ctypes.CDLL(local_lib)
            else:
                raise RuntimeError(f"Could not load {lib_path}. Please ensure it is in your library path.")

        self._setup_bindings()
        self.handle = self.lib.nanoai_create()

    def _setup_bindings(self):
        self.lib.nanoai_create.restype = ctypes.c_void_p
        self.lib.nanoai_destroy.argtypes = [ctypes.c_void_p]

        self.lib.nanoai_load_model_id.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_load_model_id.restype = ctypes.c_bool

        self.lib.nanoai_generate_id.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.nanoai_generate_id.restype = ctypes.c_char_p

        for func in ['nanoai_run_ocr', 'nanoai_run_segmentation', 'nanoai_detect_objects', 'nanoai_analyze_face', 'nanoai_analyze_document', 'nanoai_understand_report']:
            if hasattr(self.lib, func):
                f = getattr(self.lib, func)
                f.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint8), ctypes.c_int, ctypes.c_int]
                f.restype = ctypes.c_char_p

    def __del__(self):
        if hasattr(self, 'handle') and self.handle:
            self.lib.nanoai_destroy(self.handle)

    def load_model(self, model_path: str, model_id: str = "default") -> bool:
        return self.lib.nanoai_load_model_id(self.handle, model_path.encode('utf-8'), model_id.encode('utf-8'))

    def generate(self, prompt: str, model_id: str = "default") -> str:
        return self.lib.nanoai_generate_id(self.handle, prompt.encode('utf-8'), model_id.encode('utf-8')).decode('utf-8')

    def run_ocr(self, buffer, width, height) -> str:
        data_ptr = (ctypes.c_uint8 * len(buffer))(*buffer)
        return self.lib.nanoai_run_ocr(self.handle, data_ptr, width, height).decode('utf-8')

    def summarize_text(self, text: str) -> str:
        return self.lib.nanoai_summarize_text(self.handle, text.encode('utf-8')).decode('utf-8')

    @staticmethod
    def convert_model(input_path: str, output_path: str, quantization_type: int) -> bool:
        lib = ctypes.CDLL("libnanoai.so")
        lib.nanoai_convert_model.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int]
        lib.nanoai_convert_model.restype = ctypes.c_bool
        return lib.nanoai_convert_model(input_path.encode('utf-8'), output_path.encode('utf-8'), quantization_type)
