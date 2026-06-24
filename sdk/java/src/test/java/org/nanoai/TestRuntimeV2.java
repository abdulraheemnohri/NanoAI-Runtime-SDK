package org.nanoai;

public class TestRuntimeV2 {
    public static void main(String[] args) {
        NanoRuntime rt = new NanoRuntime();
        rt.loadModel("test.gguf", "chat");
        System.out.println("HAL Profile: " + rt.getHardwareProfile());
        System.out.println("Result: " + rt.generate("Hello", "chat", 0));
        rt.close();
    }
}
