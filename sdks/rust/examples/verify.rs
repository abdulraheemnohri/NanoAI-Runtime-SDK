use nanoai::NanoRuntime;

fn main() {
    let rt = NanoRuntime::new();
    let loaded = rt.load_model("test.gguf", "chat_model");
    println!("Rust Model Loaded: {}", loaded);
    let hw = rt.get_detected_hardware("chat_model");
    println!("Rust Detected HW: {}", hw);
    let res = rt.generate("Hello", "chat_model");
    println!("Rust Result: {}", res);

    if loaded && !hw.is_empty() && res.contains("GGUF Backend") {
        println!("RUST INTEGRITY TEST PASSED!");
    } else {
        eprintln!("RUST INTEGRITY TEST FAILED!");
        std::process::exit(1);
    }
}
