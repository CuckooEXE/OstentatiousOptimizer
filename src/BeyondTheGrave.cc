#include "BeyondTheGrave.hh"

using namespace llvm;

// static cl::opt<std::string> DeadCodeInputDir("asdf", cl::desc("Directory of Dead Code Bitcode"));
std::string DeadCodeInputDir = "inputs/DeadCodeSamples/build/";

bool BeyondTheGrave::runOnModule(Module& M)
{
    for (Function& F : M)
        LOG_HEAD << " Function: " << F.getName() << "\n";
    return false;
}

PreservedAnalyses BeyondTheGrave::run(llvm::Module &M, llvm::ModuleAnalysisManager &)
{
    LOG_HEAD << " DeadCodeInputDir: " << DeadCodeInputDir << "\n";
    return (runOnModule(M) ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}
