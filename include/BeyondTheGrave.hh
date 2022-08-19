/**
 * @file BeyondTheGrave.hh
 * @author Axel Persinger (axel@nullptrsec.io)
 * @brief Insert dead code (instructions/basic blocks/functions)
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BEYONDTHEGRAVE_H_
#define BEYONDTHEGRAVE_H_

#include "common.hh"
#include "llvm/Support/CommandLine.h"

#undef PASSNAME
#undef DEBUG_TYPE
#define BEYONDTHEGRAVE_PASSNAME "BeyondTheGrave"
#define PASSNAME BEYONDTHEGRAVE_PASSNAME
#define DEBUG_TYPE PASSNAME

/**
 * @brief Dynamic inlining of functions
 * 
 */
struct BeyondTheGrave : public llvm::PassInfoMixin<BeyondTheGrave> {

    /**
     * @brief Run and analyze a module
     * 
     * @param M Module to analyze
     * @return llvm::PreservedAnalyses Analysis of the module
     */
    llvm::PreservedAnalyses run(
        llvm::Module &M,
        llvm::ModuleAnalysisManager &
    );

    bool runOnModule(llvm::Module &M);
};

#endif // !BEYONDTHEGRAVE_H_