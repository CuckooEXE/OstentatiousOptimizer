CC			:= clang-14
CXX			:= clang++-14
LD			:= ld.gold
OPT			:= opt-14
BINDIR		:= bin
LIBDIR		:= lib
BUILDDIR	:= build
DOCDIR		:= docs
CFLAGS		:= -std=gnu++14
INCLUDE		:= -I$$LLVM_DIR/include/
LDFLAGS		:= 
DEBUG_FLAGS	:= -g -O0 -fno-omit-frame-pointer
REL_FLAGS	:= -O3 -fomit-frame-pointer

# pkg-config for external libraries
LLVM_CFLAGS		:= $(shell llvm-config-14 --cflags)
LLVM_LDFLAGS	:= $(shell llvm-config-14 --ldflags)


DEFAULT: OstentatiousOptimizer
.PHONY: clean

# Clean up build artifacts
clean:
	rm -rf $(BINDIR)/
	rm -rf $(LIBDIR)/
	rm -rf $(BUILDDIR)/

# Build all of OstentatiousOptimizer
OstentatiousOptimizer: $(LIBDIR)/libOstentatiousOptimizer.so
$(LIBDIR)/libOstentatiousOptimizer.so:
	mkdir -p $(LIBDIR)/
	$(CXX) $(WARNFLAGS) $(LLVM_CFLAGS) $(DEBUG_FLAGS) $(INCLUDE) -Iinclude/ -fPIC -shared -Wl,-soname,libOstentatiousOptimizer.so -o $(LIBDIR)/libOstentatiousOptimizer.so src/*.cc $(LLVM_LDFLAGS)

# Build test inputs to OstentatiousOptimizer
inputs: $(BUILDDIR)/math.ll
$(BUILDDIR)/math.ll: inputs/math.c
	mkdir -p $(BUILDDIR)/
	$(CC) -S -O0 -emit-llvm inputs/math.c -o $(BUILDDIR)/math.ll

# Test
test: inputs OstentatiousOptimizer
	mkdir -p $(BUILDDIR)/
	$(OPT) -debug-pass-manager -S -load-pass-plugin=$(LIBDIR)/libOstentatiousOptimizer.so -passes="reliner,print-functions" $(BUILDDIR)/math.ll > $(BUILDDIR)/math.relined.ll
	$(CC) -S -mllvm --x86-asm-syntax=intel -o $(BUILDDIR)/math.s $(BUILDDIR)/math.relined.ll
	$(CC) -o $(BUILDDIR)/math $(BUILDDIR)/math.relined.ll
	$(BUILDDIR)/math ; test $$? -eq 40