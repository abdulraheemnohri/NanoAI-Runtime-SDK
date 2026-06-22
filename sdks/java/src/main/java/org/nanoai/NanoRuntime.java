package org.nanoai;

import java.io.File;

public class NanoRuntime {
    private long nativeHandle;

    static {
        // Attempt to load from library path or current directory
        try {
            System.loadLibrary("nanoai");
        } catch (UnsatisfiedLinkError e) {
            String libName = System.mapLibraryName("nanoai");
            File libFile = new File(libName);
            if (libFile.exists()) {
                System.load(libFile.getAbsolutePath());
            } else {
                throw e;
            }
        }
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

    // Native methods (re-using the same JNI bridge)
    private native long nativeInit();
    private native void nativeDestroy(long handle);
    private native boolean nativeLoadModel(long handle, String modelPath);
    private native String nativeGenerate(long handle, String prompt);
}
