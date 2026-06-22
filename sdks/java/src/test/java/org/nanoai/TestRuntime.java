package org.nanoai;

public class TestRuntime {
    public static void main(String[] args) {
        NanoRuntime runtime = new NanoRuntime();
        boolean loaded = runtime.loadModel("test.gguf");
        if (loaded) {
            System.out.println("Java: Model loaded");
        }
        String result = runtime.generate("Hello from Java");
        System.out.println("Java Result: " + result);
        runtime.close();
    }
}
