from nanoai.runtime import NanoRuntime
import os
import json

def test_ultimate():
    lib_path = "../../build/libnanoai.so"
    if not os.path.exists(lib_path):
        lib_path = "build/libnanoai.so"

    rt = NanoRuntime(lib_path=lib_path)

    print("--- NRX Ultimate SDK Test ---")
    print(f"Registered Agents: {rt.get_registered_agents()}")

    health = rt.get_cluster_health()
    print(f"Cluster Health: {json.dumps(health, indent=2)}")

    print("Enabling Eco-Mode...")
    rt.set_eco_mode(True)

    rt.load_model("models/gemma.gguf", "chat_v2")
    print(f"Generate: {rt.generate('Eco-test', 'chat_v2')}")

if __name__ == "__main__":
    test_ultimate()
