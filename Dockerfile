FROM ubuntu:20.04

ENV PROJECT OstentatiousOptimizer
ENV LC_CTYPE C.UTF-8
ENV LLVM_DIR /usr/lib/llvm-14/

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

# Install software dev packages
RUN apt-get update && apt-get install -y \
    git \
    cmake \
    ninja-build \
    build-essential \
    python3-minimal python3-pip\
    wget \
    software-properties-common \
    && rm -rf /var/lib/apt/lists/*

# Install LLVM
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN apt-add-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-14 main"
RUN apt-get update
RUN apt-get install -y llvm-14 llvm-14-dev llvm-14-tools clang-14
RUN apt-get install -y python3-setuptools

# Install LIT
RUN pip3 install lit

# Add the built LLVM to the PATH
ENV PATH "$LLVM_DIR/bin:$PATH"

# Set the workdir
COPY ./ /${PROJECT}
WORKDIR /${PROJECT}