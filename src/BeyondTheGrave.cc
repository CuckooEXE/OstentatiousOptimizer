#include "BeyondTheGrave.hh"

std::vector<llvm::BasicBlock> dead_code_samples;

bool generate_samples()
{
    llvm::LLVMContext context;
    // IRBuilder<> builder(context);

    return false;
}

bool BeyondTheGrave::runOnFunction(llvm::Function& F)
{
    LOG_HEAD << " Function: " << F.getName() << "\n";


    // auto Val39 = llvm::ConstantInt::get();
    // auto Val151 = llvm::ConstantInt::get(BinOp->getType(), 151);
    // auto Val23 = llvm::ConstantInt::get(BinOp->getType(), 23);
    // auto Val2 = llvm::ConstantInt::get(BinOp->getType(), 2);
    // auto Val111 = llvm::ConstantInt::get(BinOp->getType(), 111);
    
    return false;
}

llvm::PreservedAnalyses BeyondTheGrave::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM)
{
    return (runOnFunction(F) ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}
