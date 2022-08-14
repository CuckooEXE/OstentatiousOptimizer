#include "PrintFunctions.hh"

using namespace llvm;

bool PrintFunctions::runOnModule(Module& M)
{
    for (Function& F : M)
        LOG_HEAD << "Adding always_inline to " << F.getName() << "\n";
    return false;
}

PreservedAnalyses PrintFunctions::run(llvm::Module &M,
                                       llvm::ModuleAnalysisManager &) {

  return (runOnModule(M) ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}
