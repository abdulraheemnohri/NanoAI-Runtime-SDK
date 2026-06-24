from nanoai.runtime import NanoRuntime
import os
import sys

def test():
    # Attempt to find libnanoai.so in build directory
    lib_path = "build/libnanoai.so"
    if not os.path.exists(lib_path):
        lib_path = "../../build/libnanoai.so"

    if not os.path.exists(lib_path):
        print(f"Error: Could not find libnanoai.so at {lib_path}")
        return

    rt = NanoRuntime(lib_path=lib_path)
    print(f"Hardware Profile: {rt.get_hardware_profile()}")
    rt.load_model("models/gemma.gguf", "chat")
    print(f"Generate: {rt.generate('Hello', 'chat', priority=0)}")

    print("\nTesting Swarm...")
    print(f"Swarm: {rt.run_swarm('test_task', ['CodingAgent'], 'Hello Agent')}")

    print("\nTesting Workflow...")
    print(f"Workflow: {rt.run_workflow('{\"ocr\": true}', 'data_01')}")

    print("\nTesting OS Layer...")
    if rt.boot_os():
        print(f"OS Dispatch: {rt.os_dispatch('check_disk')}")

    print(f"\nTelemetry: {rt.get_telemetry()}")

if __name__ == "__main__":
    print("=== NanoAI Python SDK v2 Integration Test ===")
    test()
