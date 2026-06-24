# NanoAI Runtime SDK v2 — Universal AI Orchestration

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)

NanoAI Runtime is a universal offline AI execution platform that intelligently orchestrates multiple models across all available hardware: **CPU, GPU, NPU, DSP, and remote LAN clusters.**

## 🚀 Key v2 Features
- **Universal HAL**: Native auto-discovery for Qualcomm Hexagon, NVIDIA CUDA, Apple Metal, AMD ROCm, and more.
- **Parallel Execution Engine**: Run LLMs, Vision, and Audio models simultaneously with priority-aware scheduling.
- **Dynamic Load Balancing**: Automatically offloads tasks to idle LAN nodes (Cluster Mode).
- **AI Agent Framework**: Built-in agents for Coding, Research, and Vision.
- **High-End Dashboard**: Real-time Mission Control for hardware telemetry and cluster health.
- **Multi-Language SDKs**: Native support for **Android/Java, Python, Rust, NodeJS, and C++.**

## 📂 Architecture
- `core/`: C++ Orchestration Layer.
- `cluster/`: P2P Node Discovery and Synchronization.
- `backends/`: Vendor-specific hardware plugins.
- `dashboard/`: Visual telemetry interface.

## 📦 Quick Start (NodeJS)
```javascript
const { NanoRuntime } = require('nanoai');
const rt = new NanoRuntime();

rt.loadModel('gemma-3b.gguf', 'chat');
const response = rt.generate('Explain Quantum Physics', 'chat', 0); // Critical priority
console.log(rt.getTelemetry());
```

## 💰 Sustainability
NanoAI is donation-funded via GitHub Sponsors and OpenCollective. Enterprise tiers available for custom silicon optimization.
