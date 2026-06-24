package org.nanoai;

public class NanoRuntime {
    private long handle;

    static {
        System.loadLibrary("nanoai");
    }

    public NanoRuntime() {
        handle = nativeInit();
    }

    public void close() {
        if (handle != 0) {
            nativeDestroy(handle);
            handle = 0;
        }
    }

    public boolean loadModel(String modelPath, String modelId) {
        return nativeLoadModel(handle, modelPath, modelId);
    }

    public String generate(String prompt, String modelId, int priority) {
        return nativeGenerate(handle, prompt, modelId, priority);
    }

    public String getRuntimeTelemetry() {
        return nativeGetTelemetry(handle);
    }

    public String getHardwareProfile() {
        return nativeGetHardwareProfile(handle);
    }

    public String getClusterNodes() {
        return nativeGetClusterNodes(handle);
    }

    private native long nativeInit();
    private native void nativeDestroy(long handle);
    private native boolean nativeLoadModel(long handle, String modelPath, String modelId);
    private native String nativeGenerate(long handle, String prompt, String modelId, int priority);
    private native String nativeGetTelemetry(long handle);
    private native String nativeGetHardwareProfile(long handle);
    private native String nativeGetClusterNodes(long handle);
}
