fn main() {
    println!("cargo:rustc-link-search=native=../../build/core");
    println!("cargo:rustc-link-lib=dylib=nanoai");
}
