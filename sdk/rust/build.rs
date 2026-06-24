use std::{env, path::PathBuf};

fn main() {
    if let Ok(dir) = env::var("NANOAI_LIB_DIR") {
        println!("cargo:rustc-link-search=native={}", dir);
        return;
    }

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let dev_build_dir = manifest_dir.join("..").join("..").join("build");
    if dev_build_dir.exists() {
        println!("cargo:rustc-link-search=native={}", dev_build_dir.display());
    }
}
