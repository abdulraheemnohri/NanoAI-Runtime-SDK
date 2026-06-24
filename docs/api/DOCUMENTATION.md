# NanoAI Runtime SDK Documentation

NanoAI is a universal offline AI runtime for running local AI models across Android, Windows, Linux, macOS, and edge devices.

## 1. Integration Guide

### Android Integration
Add the following to your `build.gradle`:
```gradle
repositories {
    maven { url 'https://maven.pkg.github.com/abdulraheemnohri/NanoAI-Runtime-SDK' }
}

dependencies {
    implementation 'org.nanoai:nanoai-android:1.0.0'
}
```

### Java Integration (Desktop)
```gradle
dependencies {
    implementation 'org.nanoai:nanoai-java:1.0.0'
}
```

### Python Integration
```bash
pip install nanoai
# Set NANOAI_LIB_PATH=/absolute/path/to/libnanoai.so
# or place libnanoai.so in LD_LIBRARY_PATH
```

### Rust Integration
```toml
[dependencies]
nanoai = "0.1"
```

Set `NANOAI_LIB_DIR` or `NANOAI_INSTALL_DIR` if `libnanoai.so` is not in a standard linker path.

### Node.js Integration
```bash
cd sdk/nodejs
npm install
# Build the root native library first:
# cmake -S . -B build && cmake --build build
```

---

## 2. Usage Examples

### Android / Kotlin Example
```kotlin
val runtime = NanoRuntime()

runtime.loadModel(
    "gemma-3n.gguf",
    "default"
)

val result = runtime.generate(
    "Explain AI",
    "default",
    2
)

println(result)
```

### Python Example
```python
from nanoai import NanoRuntime

with NanoRuntime() as rt:
    rt.load_model("gemma.gguf", "default")
    print(rt.generate("Hello", "default", 2))
    print(rt.get_runtime_telemetry())
```

### Rust Example
```rust
use nanoai::NanoRuntime;

fn main() {
    let runtime = NanoRuntime::new();
    runtime.load_model("gemma.gguf", "default");
    let res = runtime.generate("Hi", "default", 2);
    let workflow_res = runtime.run_workflow("{\"nodes\":[]}", "input");
    println!("{}", res);
    println!("{}", workflow_res);
}
```

### Java Example
```java
NanoRuntime rt = new NanoRuntime();
rt.loadModel("gemma.gguf", "default");
System.out.println(rt.generate("Hello", "default", 2));
System.out.println(rt.getRuntimeTelemetry());
rt.close();
```

---

## 3. Benefits of NanoAI

- **Offline-First**: Run powerful AI models without any internet connection.
- **Privacy-Focused**: User data hamesha device par rehta hai.
- **Cross-Platform**: Unified API for mobile, desktop, and embedded.
- **Hardware Acceleration**: Automatically choose GPU or NPU based on device capability.
- **Memory Optimized**: Features model caching, memory mapping (mmap), and lazy loading.
- **Multi-Modal**: Native support for Text, Vision, and Audio AI tasks.

---

## 4. Multi-Model Parallel Execution
NanoAI allows running multiple models in parallel by addressing them with a `modelId`.
```kotlin
runtime.loadModel("chat.gguf", "chat_model")
runtime.loadModel("ocr.onnx", "vision_model")

val chatRes = runtime.generate("Hi", "chat_model", 2)
val ocrRes = runtime.runOCR(imageBuffer, 1920, 1080) // default routing or specific ID
```

---

## 5. Model Conversion & Quantization
Optimize models for edge devices using the built-in converter.
- **Auto Quantization**: FP32 → FP16, INT8, or INT4.
- **Smaller Footprint**: Reduce model size by up to 8x.
- **Faster Inference**: Significant speedups on mobile NPUs.
