import os
import sys
import subprocess

def run_test(name, command):
    print(f"Running {name}...")
    try:
        result = subprocess.run(command, shell=True, capture_output=True, text=True, timeout=30)
        if result.returncode == 0:
            print(f"  [PASS] {name}")
            return True
        else:
            print(f"  [FAIL] {name}")
            print(f"    Error: {result.stderr}")
            return False
    except Exception as e:
        print(f"  [ERROR] {name}: {str(e)}")
        return False

def main():
    print("=== NRX Continuous Integration Smoke Test ===")

    # Ensure build exists
    if not os.path.exists("build/libnanoai.so"):
        print("Error: build/libnanoai.so not found. Run cmake/make first.")
        sys.exit(1)

    tests = [
        ("C++ Integration Test", "export LD_LIBRARY_PATH=$(pwd)/build:$LD_LIBRARY_PATH && ./build/full_system_test"),
        ("Python SDK Sanity", "export LD_LIBRARY_PATH=$(pwd)/build:$LD_LIBRARY_PATH && python3 sdk/python/test_v2.py"),
        ("HAL Discovery Check", "export LD_LIBRARY_PATH=$(pwd)/build:$LD_LIBRARY_PATH && ./build/nrx_demo | grep -i 'HAL:'")
    ]

    all_passed = True
    for name, cmd in tests:
        if not run_test(name, cmd):
            all_passed = False

    if all_passed:
        print("\nAll NRX subsystems stable.")
        sys.exit(0)
    else:
        print("\nNRX smoke test failed.")
        sys.exit(1)

if __name__ == "__main__":
    main()
