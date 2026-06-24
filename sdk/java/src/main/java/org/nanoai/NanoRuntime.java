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

    public String runSwarm(String taskName, String[] agents, String input) {
        return nativeRunSwarm(handle, taskName, agents, input);
    }

    public String runWorkflow(String workflowJson, String input) {
        return nativeRunWorkflow(handle, workflowJson, input);
    }

    public boolean bootOS() {
        return nativeBootOS(handle);
    }

    public String osDispatch(String task) {
        return nativeOSDispatch(handle, task);
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
    private native String nativeRunSwarm(long handle, String taskName, String[] agents, String input);
    private native String nativeRunWorkflow(long handle, String workflowJson, String input);
    private native boolean nativeBootOS(long handle);
    private native String nativeOSDispatch(long handle, String task);
    private native String nativeGetTelemetry(long handle);
    private native String nativeGetHardwareProfile(long handle);
    private native String nativeGetClusterNodes(long handle);
}
