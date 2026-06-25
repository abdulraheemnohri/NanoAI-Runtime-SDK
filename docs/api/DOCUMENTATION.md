# NanoAI Runtime X (NRX) v2.5 Documentation

NRX is a universal offline AI runtime designed for parallel multi-model execution and hardware-aware orchestration.

## 🚀 Key APIs

### C++ Core API
```cpp
#include "nanoai/runtime.h"

nanoai::NanoRuntime nrx;
nrx.loadModel("llama-3.gguf", "chat");
std::string res = nrx.generate("Hello", "chat");
```

### Resource Governance
- **ThermalGovernor**: Monitors system temperature and throttles workload to prevent overheating.
- **BatteryGovernor**: Adjusts execution priority and backend selection based on power levels.

### Cluster Mesh
- **Discovery**: Auto-detects LAN nodes using UDP/mDNS.
- **StateSync**: Synchronizes session context across multiple devices.
- **Replication**: Distributes model weights to edge nodes for local execution.

## 📦 Supported Model Formats
- GGUF (Llama, Gemma, etc.)
- ONNX (Vision, NLP)
- TensorFlow Lite (Edge detection)
- CoreML (Apple Silicon optimized)
- OpenVINO IR (Intel optimized)

## 🛠 Multi-Language SDKs
- **Python**: `pip install nanoai-runtime-x`
- **Node.js**: `npm install nanoai-runtime-x`
- **Rust**: `cargo add nanoai-runtime-x`
- **Java/Android**: Native JNI bridge support.
- **Go/Kotlin/RN/Flutter**: Foundational support in v2.5.
