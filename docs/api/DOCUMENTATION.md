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
# Ensure libnanoai.so is in your LD_LIBRARY_PATH
```

### Rust Integration
```toml
[dependencies]
nanoai = "1.0"
```

---

## 2. Usage Examples

### Android / Kotlin Example
```kotlin
val runtime = NanoRuntime()

runtime.loadModel(
    "gemma-3n.gguf"
)

val result = runtime.generate(
    "Explain AI"
)

println(result)
```

### Python Example
```python
from nanoai import NanoRuntime

rt = NanoRuntime()
rt.load_model("gemma.gguf")
print(rt.generate("Hello"))
```

### Rust Example
```rust
use nanoai::NanoRuntime;

fn main() {
    let runtime = NanoRuntime::new();
    runtime.load_model("gemma.gguf", "default");
    let res = runtime.generate("Hi", "default");
    println!("{}", res);
}
```

### Java Example
```java
NanoRuntime rt = new NanoRuntime();
rt.loadModel("gemma.gguf");
System.out.println(rt.generate("Hello"));
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

val chatRes = runtime.generate("Hi", "chat_model")
val ocrRes = runtime.runOCR(imageBuffer, 1920, 1080) // default routing or specific ID
```

---

## 5. Model Conversion & Quantization
Optimize models for edge devices using the built-in converter.
- **Auto Quantization**: FP32 → FP16, INT8, or INT4.
- **Smaller Footprint**: Reduce model size by up to 8x.
- **Faster Inference**: Significant speedups on mobile NPUs.
