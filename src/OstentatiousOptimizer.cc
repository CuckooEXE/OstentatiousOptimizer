#include "OstentatiousOptimizer.hh"

llvm::PassPluginLibraryInfo getInjectFuncCallPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, 
        "OstentatiousOptimizer", 
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
        PB.registerPipelineParsingCallback(
            [](llvm::StringRef Name, llvm::ModulePassManager &MPM,
                llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                if (Name == RELINER_PASSNAME) {
                    MPM.addPass(reliner());
                    return true;
                }
                return false;
            });
        PB.registerPipelineParsingCallback(
            [](llvm::StringRef Name, llvm::ModulePassManager &MPM,
                llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                if (Name == PRINTFUNCTIONS_PASSNAME) {
                    MPM.addPass(PrintFunctions());
                    return true;
                }
                return false;
            });
        PB.registerPipelineParsingCallback(
            [](llvm::StringRef Name, llvm::FunctionPassManager &FPM,
                llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                if (Name == BEYONDTHEGRAVE_PASSNAME) {
                    FPM.addPass(BeyondTheGrave());
                    return true;
                }
                return false;
            });
        }
    };
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getInjectFuncCallPluginInfo();
}
