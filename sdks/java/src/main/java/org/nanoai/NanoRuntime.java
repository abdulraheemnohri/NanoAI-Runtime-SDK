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

    public boolean loadModel(String modelPath) {
        return nativeLoadModel(handle, modelPath, "default");
    }

    public boolean loadModel(String modelPath, String modelId) {
        return nativeLoadModel(handle, modelPath, modelId);
    }

    public String generate(String prompt) {
        return nativeGenerate(handle, prompt, "default");
    }

    public String generate(String prompt, String modelId) {
        return nativeGenerate(handle, prompt, modelId);
    }

    public String getDetectedHardware() {
        return nativeGetDetectedHardware(handle, "default");
    }

    public String getDetectedHardware(String modelId) {
        return nativeGetDetectedHardware(handle, modelId);
    }

    public static boolean convertModel(String inputPath, String outputPath, int quantizationType) {
        return nativeConvertModel(inputPath, outputPath, quantizationType);
    }

    private native long nativeInit();
    private native void nativeDestroy(long handle);
    private native boolean nativeLoadModel(long handle, String modelPath, String modelId);
    private native String nativeGenerate(long handle, String prompt, String modelId);
    private native String nativeGetDetectedHardware(long handle, String modelId);
    private static native boolean nativeConvertModel(String inputPath, String outputPath, int quantizationType);
}
