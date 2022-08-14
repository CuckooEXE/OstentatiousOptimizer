[![CodeQL Analysis](https://github.com/CuckooEXE/OstentatiousOptimizer/actions/workflows/codeql-analysis.yml/badge.svg?branch=main)](https://github.com/CuckooEXE/OstentatiousOptimizer/actions/workflows/codeql-analysis.yml)
[![Publish Docker Image](https://github.com/CuckooEXE/OstentatiousOptimizer/actions/workflows/docker-publish.yml/badge.svg?branch=main)](https://github.com/CuckooEXE/OstentatiousOptimizer/actions/workflows/docker-publish.yml)
[![Test Code](https://github.com/CuckooEXE/OstentatiousOptimizer/actions/workflows/code-test.yml/badge.svg?branch=main)](https://github.com/CuckooEXE/OstentatiousOptimizer/actions/workflows/code-test.yml)

# OstentatiousOptimizer
OstentatiousOptimizer is a project that uses the LLVM toolchain to obfuscate binaries to make reverse-engineering and attribution more difficult.

The OstentatiousOptimizer works by creating multiple [LLVM `opt`](https://www.llvm.org/docs/CommandGuide/opt.html) ["Passses"](https://releases.llvm.org/14.0.0/docs/WritingAnLLVMPass.html#introduction-what-is-a-pass), and allowing you to apply any number of them against your code base. Rather than the normal optimization passes, such as dead code elimination, `memcpy` optimization, memory to register promtions, etc. OstentatiousOptimizer will instead run obfuscation passes to try and make the code more complicated to reverse-engineer(while not affecting the runtime of the code).

## Building
To build and test the project, you can use the Docker image on GHCR or build it yourself:
```bash
$ # Build the Docker Image
$ ./start-environment.sh
```
```bash
$ # Pull image from GHCR
$ sudo docker run -it --rm ghcr.io/cuckooexe/ostentatiousoptimizer
```

Then you can just use Make:
```bash
$ make clean test
```

## Passes
The following are passes that are (or will be) included in OstentatiousOptimizer.

Status:
 - [ ] `reliner`
 - [ ] `OpaquePredicates`
 - [ ] Dead Instruction Injection
 - [ ] Dead Code Injection
 - [ ] Dead Function Injection
 - [ ] Hell's Gate
 - [ ] Basic Block Scrambler

### reliner
`reliner` will intelligently inline functions for some number of `call` instructions. That is, if there is a function, `foo`, which is called five times, it might be inlined for zero, one, or up to five of the call instructions.

### OpaquePredicates
`OpaquePredicates`  implements multiple classes of [opaque predicates](https://en.wikipedia.org/wiki/Opaque_predicate) which will obfuscate the control flow graph of the binary. 

### Dead Instruction Injection
`DJI` will inject instructions that will never be executed by ensuring that calls and jumps avoid executing the injected instructions.

### Dead Code Injection
`DCI` will inject code blocks that will never be executed by ensuring that calls and jumps avoid executing the injected blocks.

### Dead Function Injection
`DFI` will inject entire functions (try giving it functions from OSS projects!) that will never be executed by ensuring that calls and jumps avoid executing the injected functions.

### Hell's Gate
[Hell's Gate](https://vxug.fakedoma.in/papers/VXUG/Exclusive/HellsGate.pdf) implementation in LLVM IR that will automatically translate Windows API Calls into "direct syscalls" whenever possible.

### Basic Block Scrambler
Scramble Basic Blocks within a function and execute the appropriate relative jumps to maintain proper code flow.
