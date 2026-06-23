use nanoai::NanoRuntime;

fn main() {
    let runtime = NanoRuntime::new();

    if runtime.load_model("test.gguf", "default") {
        println!("Rust: Model loaded");
    }

    let result = runtime.generate("Hello from Rust", "default");
    println!("Rust Result: {}", result);
}
