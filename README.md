# NanoAI Runtime SDK v2 — Universal AI Orchestration

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)

NanoAI Runtime is a universal offline AI execution platform capable of running multiple AI models simultaneously across all available hardware resources. Unlike traditional runtimes, NanoAI acts as an AI Operating Layer that intelligently orchestrates workloads across CPU, GPU, NPU, and distributed clusters.

## 🚀 Key v2 Features
- **Parallel Multi-Model Execution Engine**: Run Llama, Whisper, and YOLO simultaneously.
- **Universal HAL**: Native support for Qualcomm Hexagon, NVIDIA CUDA, Apple Metal, and more.
- **AI Agent Framework**: Built-in Coding, Research, and Vision agents.
- **Distributed Cluster Mode**: Turn multiple LAN devices into a single AI supercomputer.
- **Security Sandbox**: Isolated model execution for maximum privacy.
- **Real-time Telemetry**: Monitor NPU/GPU load, temperature, and tokens/sec.

## 📂 Project Structure
- `core/`: The C++ orchestration engine (Scheduler, HAL, Agents, Telemetry).
- `backends/`: Vendor-specific hardware plugins (NVIDIA, Qualcomm, Apple, etc.).
- `sdk/`: High-level wrappers for Android, Java, Python, Rust, and C++.
- `docs/`: Deep dive into API and Architecture.

## 📦 Quick Start (v2 Parallel API)
```cpp
NanoRuntime runtime;
runtime.loadModel("gemma.gguf", "chat");
runtime.loadModel("whisper.onnx", "voice");

// Execute parallelly with priority
runtime.generate("Hello", "chat", TaskPriority::CRITICAL);
runtime.generate("Transcribe", "voice", TaskPriority::NORMAL);
```

## 💰 Sustainability
NanoAI is donation-funded (GitHub Sponsors, OpenCollective). Commercial support available for Enterprise. See docs for details.
