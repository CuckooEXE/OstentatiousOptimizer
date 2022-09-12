/**
 * @file BBScrambler.hh
 * @author Axel Persinger (axel@nullptrsec.io)
 * @brief Scramble Basic Blocks within a function
 * @version 0.1
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BBSCRAMBLER_H_
#define BBSCRAMBLER_H_

#include "common.hh"
#include <llvm/IR/IRBuilder.h>

#undef PASSNAME
#undef DEBUG_TYPE
#define BBSCRAMBLER_PASSNAME "BBScrambler"
#define PASSNAME BBSCRAMBLER_PASSNAME
#define DEBUG_TYPE PASSNAME

/**
 * @brief Dynamic inlining of functions
 * 
 */
struct BBScrambler : public llvm::PassInfoMixin<BBScrambler> {

    /**
     * @brief Run and analyze a module
     * 
     * @param M Module to analyze
     * @return llvm::PreservedAnalyses Analysis of the module
     */
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);


    bool runOnFunction(llvm::Function& F);
};

#endif // !BBSCRAMBLER_H_