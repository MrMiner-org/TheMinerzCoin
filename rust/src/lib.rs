use secp256k1::ecdsa::Signature;
use secp256k1::{Message, PublicKey, Secp256k1};
use bitcoin_hashes::{sha256, Hash};
use core::convert::TryInto;

#[cxx::bridge]
mod ffi {
    extern "Rust" {
        fn verify_ecdsa(msg: &[u8], sig: &[u8], pubkey: &[u8]) -> bool;
    }
}

pub fn verify_ecdsa(msg: &[u8], sig: &[u8], pubkey: &[u8]) -> bool {
    let secp = Secp256k1::verification_only();
    let digest: [u8; 32] = if msg.len() == 32 {
        match msg.try_into() {
            Ok(arr) => arr,
            Err(_) => return false,
        }
    } else {
        sha256::Hash::hash(msg).to_byte_array()
    };
    let msg = Message::from_digest(digest);
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
