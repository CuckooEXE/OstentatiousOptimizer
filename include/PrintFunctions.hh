/**
 * @file PrintFunctions.hh
 * @author Axel Persinger (axel@nullptrsec.io)
 * @brief Print function names
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PRINTFUNCTIONS_H_
#define PRINTFUNCTIONS_H_

#include "common.hh"

#undef PASSNAME
#undef DEBUG_TYPE
#define RELINER_PASSNAME "print-functions"
#define PASSNAME RELINER_PASSNAME
#define DEBUG_TYPE PASSNAME

/**
 * @brief Dynamic inlining of functions
 * 
 */
struct PrintFunctions : public llvm::PassInfoMixin<PrintFunctions> {

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

#endif // !PRINTFUNCTIONS_H_