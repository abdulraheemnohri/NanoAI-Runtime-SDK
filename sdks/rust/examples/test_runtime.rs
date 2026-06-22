use nanoai::NanoRuntime;

fn main() {
    let runtime = NanoRuntime::new();

    if runtime.load_model("test.gguf") {
        println!("Rust: Model loaded");
    }

    let result = runtime.generate("Hello from Rust");
    println!("Rust Result: {}", result);
}
