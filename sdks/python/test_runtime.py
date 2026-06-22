import os
import sys

# Add the local nanoai package to path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__))))

from nanoai import NanoRuntime

def test():
    # Points to the built library
    lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../build/core/libnanoai.so"))

    runtime = NanoRuntime(lib_path=lib_path)

    if runtime.load_model("test.onnx"):
        print("Python: Model loaded")

    result = runtime.generate("Hello from Python")
    print(f"Python Result: {result}")

if __name__ == "__main__":
    test()
