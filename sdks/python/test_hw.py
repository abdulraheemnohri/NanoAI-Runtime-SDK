from nanoai.runtime import NanoRuntime
import os

# Ensure libnanoai.so is in the path
rt = NanoRuntime(lib_path="./libnanoai.so")
rt.load_model("test.gguf", "chat_model")
hw = rt.get_detected_hardware("chat_model")
print(f"Python detected: {hw}")
assert hw != "Unknown"
print("Python HW test passed!")
