FROM ubuntu:20.04

ENV PROJECT OstentatiousOptimizer
ENV LC_CTYPE C.UTF-8

# tzdata Docker work around
ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN true
RUN truncate -s0 /tmp/preseed.cfg; \
    echo "tzdata tzdata/Areas select Europe" >> /tmp/preseed.cfg; \
    echo "tzdata tzdata/Zones/Europe select Berlin" >> /tmp/preseed.cfg; \
    debconf-set-selections /tmp/preseed.cfg && \
    rm -f /etc/timezone /etc/localtime && \
    apt-get update && \
    apt-get install -y tzdata
RUN rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install dependencies
RUN apt update && \
    apt upgrade -y && \
    apt install -y git cmake ninja-build build-essential python3 python3-pip wget software-properties-common

# Install LLVM
ENV LLVM_DIR /opt/llvm
RUN git clone --branch release/14.x --depth 1 https://github.com/llvm/llvm-project
RUN mkdir -p $LLVM_DIR
RUN mkdir -p llvm-project/build
WORKDIR /llvm-project/build
RUN cmake -G Ninja \
        -DLLVM_ENABLE_PROJECTS=clang \
        -DLLVM_TARGETS_TO_BUILD="X86;AArch64;Mips;WebAssembly" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$LLVM_DIR \
        -DLLVM_INSTALL_UTILS=ON \
        -DLLVM_USE_LINKER=gold \
        ../llvm
RUN cmake --build . --target install
WORKDIR /

# Add the built LLVM to the PATH
ENV PATH "$LLVM_DIR/bin:$PATH"

# Install the LIT package
RUN pip3 install lit

# Set the workdir
COPY ./ /${PROJECT}
WORKDIR /${PROJECT}