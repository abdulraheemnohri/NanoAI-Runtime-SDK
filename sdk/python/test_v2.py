from nanoai.runtime import NanoRuntime
import os

def test():
    # In production, libnanoai.so would be in the system path
    rt = NanoRuntime(lib_path="./libnanoai.so")
    print(f"Hardware Profile: {rt.get_hardware_profile()}")
    rt.load_model("gemma.gguf", "chat")
    print(f"Generate: {rt.generate('Hello', 'chat', priority=0)}")
    print(f"Telemetry: {rt.get_telemetry()}")

if __name__ == "__main__":
    print("Python SDK v2 Test (Requires libnanoai.so in current dir)")
