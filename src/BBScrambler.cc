#include "BBScrambler.hh"

bool BBScrambler::runOnFunction(llvm::Function& F)
{
    LOG_HEAD << " Function: " << F.getName() << "\n";

    for (llvm::BasicBlock& bb : F)
        LOG_HEAD << " BasicBlock Instruction Count: " << bb.getInstList().size() << "\n";
    
    return false;
}

llvm::PreservedAnalyses BBScrambler::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM)
{
    return (runOnFunction(F) ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}
