const { NanoRuntime } = require('./index.js');

async function test() {
    console.log("=== NanoAI Node.js SDK v2 Integration Test ===");
    try {
        const rt = new NanoRuntime();
        console.log("Hardware Profile:", rt.getHardwareProfile());
        rt.loadModel("models/llama3.gguf", "chat");
        console.log("Generate:", rt.generate("Hello", "chat", 0));
        console.log("\nTesting Swarm...");
        console.log("Swarm:", rt.runSwarm("node_task", ["ResearchAgent"], "Gather info on AI"));
        console.log("\nTesting Workflow...");
        console.log("Workflow:", rt.runWorkflow({"translate": true}, "text_to_fix"));
        console.log("\nTesting OS Layer...");
        if (rt.bootOS()) {
            console.log("OS Dispatch:", rt.osDispatch("cleanup_cache"));
        }
        console.log("\nTelemetry:", rt.getTelemetry());
    } catch (e) {
        console.error("Test failed:", e.message);
    }
}
test();
