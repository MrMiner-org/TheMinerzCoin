FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y build-essential cmake libssl-dev
WORKDIR /build
COPY . .
RUN cmake -S . -B build && cmake --build build -j$(nproc)

FROM ubuntu:22.04
COPY --from=builder /build/build/theminerzcoind /usr/local/bin/theminerzcoind
ENTRYPOINT ["theminerzcoind"]
