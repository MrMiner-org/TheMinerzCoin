use secp256k1::{Secp256k1, Message, PublicKey};
use secp256k1::ecdsa::Signature;

#[cxx::bridge]
mod ffi {
    extern "Rust" {
        fn verify_ecdsa(msg: &[u8], sig: &[u8], pubkey: &[u8]) -> bool;
    }
}

pub fn verify_ecdsa(msg: &[u8], sig: &[u8], pubkey: &[u8]) -> bool {
    let secp = Secp256k1::verification_only();
    let msg = match Message::from_slice(msg) {
        Ok(m) => m,
        Err(_) => return false,
    };
    let sig = match Signature::from_der(sig) {
        Ok(s) => s,
        Err(_) => return false,
    };
    let pk = match PublicKey::from_slice(pubkey) {
        Ok(p) => p,
        Err(_) => return false,
    };
    secp.verify_ecdsa(msg, &sig, &pk).is_ok()
}
