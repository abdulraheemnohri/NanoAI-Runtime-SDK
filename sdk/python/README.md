# NanoAI Python SDK

```python
from nanoai import NanoRuntime

rt = NanoRuntime()
rt.load_model("gemma-3b.gguf", "chat")
print(rt.generate("Hello", "chat"))
```
