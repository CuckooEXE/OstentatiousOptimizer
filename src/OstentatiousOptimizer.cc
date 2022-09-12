#include "OstentatiousOptimizer.hh"

llvm::PassPluginLibraryInfo getInjectFuncCallPluginInfo() 
{

    // TODO: Instead of copy/pasting the blocks below, loop over 
    //          this vector.
    // std::vector<std::tuple<std::string, llvm::Pass>> passes = {
    //     {RELINER_PASSNAME, reliner()},
    //     {PRINTFUNCTIONS_PASSNAME, PrintFunctions()},
    //     {BEYONDTHEGRAVE_PASSNAME, BeyondTheGrave()},
    //     {BBSCRAMBLER_PASSNAME, BBScrambler()},
    // };


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
        PB.registerPipelineParsingCallback(
            [](llvm::StringRef Name, llvm::FunctionPassManager &FPM,
                llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                if (Name == BBSCRAMBLER_PASSNAME) {
                    FPM.addPass(BBScrambler());
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
