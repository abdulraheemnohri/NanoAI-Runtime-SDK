package org.nanoai;

import java.io.File;

public class NanoRuntime {
    private long nativeHandle;

    static {
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

    public String runOCR(byte[] buffer, int width, int height) {
        return nativeRunOCR(nativeHandle, buffer, width, height);
    }

    public String runSegmentation(byte[] buffer, int width, int height) {
        return nativeRunSegmentation(nativeHandle, buffer, width, height);
    }

    public String detectObjects(byte[] buffer, int width, int height) {
        return nativeDetectObjects(nativeHandle, buffer, width, height);
    }

    public String analyzeFace(byte[] buffer, int width, int height) {
        return nativeAnalyzeFace(nativeHandle, buffer, width, height);
    }

    public String recognizeSpeech(float[] samples) {
        return nativeRecognizeSpeech(nativeHandle, samples);
    }

    public String detectWakeWord(float[] samples) {
        return nativeDetectWakeWord(nativeHandle, samples);
    }

    public String summarizeText(String text) {
        return nativeSummarizeText(nativeHandle, text);
    }

    public String translateText(String text) {
        return nativeTranslateText(nativeHandle, text);
    }

    public String classifyText(String text) {
        return nativeClassifyText(nativeHandle, text);
    }

    public static boolean convertModel(String inputPath, String outputPath, int quantizationType) {
        return nativeConvertModel(inputPath, outputPath, quantizationType);
    }

    // Native methods
    private native long nativeInit();
    private native void nativeDestroy(long handle);
    private native boolean nativeLoadModel(long handle, String modelPath);
    private native String nativeGenerate(long handle, String prompt);
    private native String nativeRunOCR(long handle, byte[] buffer, int width, int height);
    private native String nativeRunSegmentation(long handle, byte[] buffer, int width, int height);
    private native String nativeDetectObjects(long handle, byte[] buffer, int width, int height);
    private native String nativeAnalyzeFace(long handle, byte[] buffer, int width, int height);
    private native String nativeRecognizeSpeech(long handle, float[] samples);
    private native String nativeDetectWakeWord(long handle, float[] samples);
    private native String nativeSummarizeText(long handle, String text);
    private native String nativeTranslateText(long handle, String text);
    private native String nativeClassifyText(long handle, String text);
    private static native boolean nativeConvertModel(String inputPath, String outputPath, int quantizationType);
}
