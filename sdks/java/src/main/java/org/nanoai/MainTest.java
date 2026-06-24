package org.nanoai;

public class MainTest {
    public static void main(String[] args) {
        NanoRuntime rt = new NanoRuntime();
        boolean loaded = rt.loadModel("test.gguf", "chat_model");
        System.out.println("Java Model Loaded: " + loaded);
        String hw = rt.getDetectedHardware("chat_model");
        System.out.println("Java Detected HW: " + hw);
        String res = rt.generate("Hello", "chat_model");
        System.out.println("Java Result: " + res);

        if (loaded && !hw.isEmpty() && res.contains("GGUF Backend")) {
            System.out.println("JAVA INTEGRITY TEST PASSED!");
        } else {
            System.err.println("JAVA INTEGRITY TEST FAILED!");
            System.exit(1);
        }
        rt.close();
    }
}
