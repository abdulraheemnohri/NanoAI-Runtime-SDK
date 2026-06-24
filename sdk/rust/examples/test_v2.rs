use nanoai::NanoRuntime;
use std::thread;
use std::time::Duration;

fn main() {
    println!("=== NanoAI Rust SDK v2 Integration Test ===");
    let rt = NanoRuntime::new();
    println!("Hardware Profile: {}", rt.get_hardware_profile());
    rt.load_model("models/llama3.gguf", "chat");
    println!("Generate: {}", rt.generate("Hello", "chat", 0));
    println!("\nTesting Swarm...");
    println!("Swarm: {}", rt.run_swarm("rust_task", &["ResearchAgent", "CodingAgent"], "Build an AI mesh"));
    println!("\nTesting Workflow...");
    println!("Workflow: {}", rt.run_workflow("{\"ocr\": true, \"translate\": true}", "input_img"));
    println!("\nTesting OS Layer...");
    if rt.boot_os() {
        println!("OS Dispatch: {}", rt.os_dispatch("optimize_memory"));
    }
    thread::sleep(Duration::from_secs(3));
    println!("Cluster Nodes: {}", rt.get_cluster_nodes());
    println!("\nTelemetry: {}", rt.get_telemetry());
}
