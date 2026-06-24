package org.nanoai

class NanoRuntime : AutoCloseable {
    private var handle: Long = 0

    init {
        System.loadLibrary("nanoai")
        handle = nativeInit()
    }

    override fun close() {
        if (handle != 0L) {
            nativeDestroy(handle)
            handle = 0
        }
    }

    fun loadModel(path: String, id: String): Boolean = nativeLoadModel(handle, path, id)
    fun generate(prompt: String, id: String, priority: Int): String = nativeGenerate(handle, prompt, id, priority)

    private external fun nativeInit(): Long
    private external fun nativeDestroy(handle: Long)
    private external fun nativeLoadModel(handle: Long, path: String, id: String): Boolean
    private external fun nativeGenerate(handle: Long, prompt: String, id: String, priority: Int): String
}
