# NanoAI Runtime X (NRX) — Universal AI Orchestration Platform

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)

NanoAI Runtime X (NRX) is a universal offline AI execution platform that intelligently orchestrates multiple models across all available hardware: **CPU, GPU, NPU, DSP, and remote LAN clusters.**

## 🚀 Key NRX Features
- **Universal HAL**: Native discovery for Qualcomm Hexagon, NVIDIA CUDA, Apple Metal, AMD ROCm.
- **Parallel Inference Engine**: Multi-worker concurrent execution for LLMs, Vision, and Audio.
- **Dynamic Load Balancing**: Priority-aware scheduling and cluster offloading.
- **AI Agent Swarm**: Collaborative agents for Coding, Research, and Vision.
- **Advanced Dashboard**: Real-time Mission Control for hardware telemetry and cluster health.
- **Multi-Language SDKs**: Native support for **Android/Java, Python, Rust, NodeJS, and C++.**

## 📂 Architecture (NRX Standard)
- `core/`: Runtime Engine, Parallel Scheduler, and OS Layer.
- `hal/`: Hardware Abstraction and Vendor Backends.
- `cluster/`: P2P Node Discovery and Mesh Synchronization.
- `dashboard/`: Visual telemetry and orchestration interface.

## 📦 Quick Start (NodeJS)
```javascript
const { NanoRuntime } = require('nanoai');
const nrx = new NanoRuntime();

nrx.loadModel('llama-3.gguf', 'chat');
const response = nrx.generate('Execute system diagnostics', 'chat', 0);
console.log(nrx.getTelemetry());
```

## 💰 Sustainability
NanoAI is donation-funded via GitHub Sponsors and OpenCollective. Supporting open-source edge AI for everyone.
