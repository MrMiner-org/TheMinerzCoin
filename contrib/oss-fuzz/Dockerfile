FROM gcr.io/oss-fuzz-base/base-builder

RUN apt-get update && apt-get install -y cmake build-essential

COPY . $SRC/TheMinerzCoin
WORKDIR $SRC/TheMinerzCoin

RUN cmake -S . -B build -DCMAKE_CXX_FLAGS="-fsanitize=fuzzer,address" -DCMAKE_C_FLAGS="-fsanitize=fuzzer,address"
RUN cmake --build build -j$(nproc) --target tx_deser_fuzz block_deser_fuzz script_interpreter_fuzz

RUN cp build/src/test/fuzz/*_fuzz $OUT/
