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

### C++ Integration
Include headers from `sdks/cpp/include` and link against `libnanoai.so`.

---

## 2. Usage Guide

### Simple Text Generation (Kotlin/Android)
```kotlin
val runtime = NanoRuntime()
runtime.loadModel("gemma-2b.gguf")
val response = runtime.generate("Hello, who are you?")
println(response)
```

### Vision Tasks (OCR) - JNI Example
```cpp
// C API
const char* text = nanoai_run_ocr(handle, image_buffer, 1920, 1080);
```

### Audio Tasks (Wake Word)
```cpp
// C API
const char* detected = nanoai_detect_wake_word(handle, audio_samples, 16000);
```

---

## 3. Benefits of NanoAI

- **Offline-First**: Run powerful AI models without any internet connection.
- **Privacy-Focused**: User data never leaves the device.
- **Cross-Platform**: Unified API for mobile, desktop, and embedded.
- **Smart Acceleration**: Automatic detection and utilization of GPU and NPU hardware.
- **Memory Optimized**: Features model caching, memory mapping, and lazy loading for low-resource environments.
- **Multi-Modal**: Native support for Text, Vision, and Audio AI tasks.

---

## 4. Supported Formats
- GGUF (Gemma, Llama, Phi)
- ONNX Runtime
- TensorFlow Lite / LiteRT
- OpenVINO
- PyTorch Export Models
