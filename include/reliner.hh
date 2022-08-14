/**
 * @file reliner.hh
 * @author Axel Persinger (axel@nullptrsec.io)
 * @brief Dynamically inline functions for some number of calls
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef RELINER_H_
#define RELINER_H_

#include "common.hh"

#undef PASSNAME
#undef DEBUG_TYPE
#define PRINTFUNCTIONS_PASSNAME "reliner"
#define PASSNAME PRINTFUNCTIONS_PASSNAME
#define DEBUG_TYPE PASSNAME
/**
 * @brief Dynamic inlining of functions
 * 
 */
struct reliner : public llvm::PassInfoMixin<reliner> {

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

#endif // !RELINER_H_