use std::{env, fs, path::PathBuf};

fn main() {
    cxx_build::bridge("src/lib.rs").compile("theminerz_rust");
    println!("cargo:rerun-if-changed=src/lib.rs");

    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let header = out_dir
        .join("cxxbridge")
        .join("include")
        .join("theminerz_rust")
        .join("src")
        .join("lib.rs.h");
    let dest = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap())
        .parent()
        .unwrap()
        .join("src")
        .join("rust_bindings");
    fs::create_dir_all(&dest).unwrap();
    let dest_file = dest.join("secp256k1.h");
    fs::copy(&header, &dest_file).unwrap();

    const MIT_HEADER: &str = concat!(
        "// Copyright (c) 2018-2022 The TheMinerzCoin developers\n",
        "// Copyright (c) 2014-2018 The TheMinerzCoin Developers\n",
        "// Copyright (c) 2013-2014 The NovaCoin Developers\n",
        "// Copyright (c) 2011-2013 The PPCoin Developers\n",
        "// Copyright (c) 2009-2016 The Bitcoin Core developers\n",
        "// Distributed under the MIT software license, see the accompanying\n",
        "// file COPYING or http://www.opensource.org/licenses/mit-license.php.\n\n",
    );

    let contents = fs::read_to_string(&dest_file).unwrap();
    fs::write(&dest_file, format!("{}{}", MIT_HEADER, contents)).unwrap();
}
