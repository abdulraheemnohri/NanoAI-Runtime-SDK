# Hardware Backend Plugin System

NanoAI Runtime uses a modular plugin architecture. Each vendor-specific backend is isolated in its own directory:

- `backends/nvidia/`: CUDA, TensorRT
- `backends/qualcomm/`: Hexagon NPU/DSP
- `backends/apple/`: Metal, CoreML
- `backends/google/`: Edge TPU
- ...and more.

### Implementing a New Backend
To add support for a new chip, implement the `HardwareDevice` interface and register it with the `HardwareAbstractionLayer`.
