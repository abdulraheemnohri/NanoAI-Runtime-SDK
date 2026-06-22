package org.nanoai;

public class NanoRuntime {
    private long nativeHandle;

    static {
        System.loadLibrary("nanoai");
    }

    public NanoRuntime() {
        this.nativeHandle = nativeInit();
    }

    public void close() {
        if (nativeHandle != 0) {
            nativeDestroy(nativeHandle);
            nativeHandle = 0;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        close();
        super.finalize();
    }

    public boolean loadModel(String modelPath) {
        if (nativeHandle == 0) return false;
        return nativeLoadModel(nativeHandle, modelPath);
    }

    public String generate(String prompt) {
        if (nativeHandle == 0) return "Runtime not initialized";
        return nativeGenerate(nativeHandle, prompt);
    }

    // Native methods
    private native long nativeInit();
    private native void nativeDestroy(long handle);
    private native boolean nativeLoadModel(long handle, String modelPath);
    private native String nativeGenerate(long handle, String prompt);
}
