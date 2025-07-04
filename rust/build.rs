use std::{env,fs,path::PathBuf};

fn main() {
    cxx_build::bridge("src/lib.rs").compile("theminerz_rust");
    println!("cargo:rerun-if-changed=src/lib.rs");

    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let header = out_dir.join("cxxbridge").join("include")
        .join("theminerz_rust").join("src").join("lib.rs.h");
    let dest = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap())
        .parent().unwrap()
        .join("src").join("rust_bindings");
    fs::create_dir_all(&dest).unwrap();
    fs::copy(header, dest.join("secp256k1.h")).unwrap();
}
