# This Makefile is responsible for going into each DeadCodeSamples directory and building all, or some, of the project as LLVM IR.
#	As you can see, it's a pretty manual and imperfect process; however, as this code will never execute, it doesn't matter.
CC			:= clang
BUILDDIR	:= output

default: git awk
clean:
	rm -rf $(BUILDDIR)/git/
	rm -rf $(BUILDDIR)/awk/
	rm -rf $(BUILDDIR)/

git: output/git*.ll
output/git*.ll: git/
	mkdir -p $(BUILDDIR)/git/
	$(CC) -S -O0 -emit-llvm -DNO_OPENSSL -Igit/ git/str*.c
	mv *.ll $(BUILDDIR)/git/

awk: output/awk*.ll
output/awk*.ll: awk/
	mkdir -p $(BUILDDIR)/awk/
	$(CC) -S -O0 -emit-llvm -Iawk/ awk/lib.c
	$(CC) -S -O0 -emit-llvm -Iawk/ awk/tran.c
	mv *.ll $(BUILDDIR)/awk/