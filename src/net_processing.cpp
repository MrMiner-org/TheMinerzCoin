if (pfrom->nVersion < 113000) {
    pfrom->fDisconnect = true;
    return error("Using old version, disconnecting peer.");
}
