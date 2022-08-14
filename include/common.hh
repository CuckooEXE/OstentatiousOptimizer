#pragma once
#ifndef COMMON_H_
#define COMMON_H_

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CommandLine.h"

/** @brief Stringification macro (pt. 2) */
#define xstr(s) str(s)

/** @brief Stringification macro (pt. 1) */
#define str(s) #s

#define LOG_HEAD errs() << "(" << PASSNAME << "): "
#endif // !COMMON_H_