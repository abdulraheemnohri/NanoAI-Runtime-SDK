package org.nanoai;

public class TestRuntimeV2 {
    public static void main(String[] args) throws Exception {
        System.out.println("=== NanoAI Java SDK v2 Integration Test ===");

        NanoRuntime rt = new NanoRuntime();
        System.out.println("Hardware Profile: " + rt.getHardwareProfile());

        rt.loadModel("models/gemma.gguf", "chat");
        System.out.println("Generate: " + rt.generate("Hello from Java", "chat", 0));

        System.out.println("\nTesting Swarm...");
        String[] agents = {"ResearchAgent", "VisionAgent"};
        System.out.println("Swarm: " + rt.runSwarm("java_task", agents, "Analyze satellite imagery"));

        System.out.println("\nTesting Workflow...");
        System.out.println("Workflow: " + rt.runWorkflow("{\"ocr\": true}", "img_001"));

        System.out.println("\nTesting OS Layer...");
        if (rt.bootOS()) {
            System.out.println("OS Dispatch: " + rt.osDispatch("reclaim_npu"));
        }

        Thread.sleep(3000);
        System.out.println("Cluster Nodes: " + rt.getClusterNodes());
        System.out.println("\nTelemetry: " + rt.getRuntimeTelemetry());

        rt.close();
    }
}
