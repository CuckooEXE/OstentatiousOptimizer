#include "reliner.hh"

using namespace llvm;

// static cl::opt<std::string> InputFilename("mypass_option", cl::desc("Specify input filename for mypass"), cl::value_desc("filename"));
// static cl::opt

bool reliner::runOnModule(Module& M)
{
    for (Function& F : M) { // Iterate over every function in the Module
        LOG_HEAD << "Adding always_inline to " << F.getName() << "\n";
        F.removeFnAttr(Attribute::OptimizeNone);
        F.removeFnAttr(Attribute::NoInline);
        F.addFnAttr(Attribute::AlwaysInline);
    }
    return true;
}

PreservedAnalyses reliner::run(llvm::Module &M,
                                       llvm::ModuleAnalysisManager &) {

  return (runOnModule(M) ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}
