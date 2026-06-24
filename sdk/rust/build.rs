use std::{env, path::PathBuf};

fn main() {
    println!("cargo:rerun-if-env-changed=NANOAI_LIB_DIR");
    println!("cargo:rerun-if-env-changed=NANOAI_INSTALL_DIR");

    if let Ok(dir) = env::var("NANOAI_LIB_DIR") {
        println!("cargo:rustc-link-search=native={}", dir);
        return;
    }

    if let Ok(prefix) = env::var("NANOAI_INSTALL_DIR") {
        let install_lib_dir = PathBuf::from(prefix).join("lib");
        if install_lib_dir.exists() {
            println!("cargo:rustc-link-search=native={}", install_lib_dir.display());
            return;
        }
    }

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let dev_build_dir = manifest_dir.join("..").join("..").join("build");
    if dev_build_dir.exists() {
        println!("cargo:rustc-link-search=native={}", dev_build_dir.display());
    }
}
