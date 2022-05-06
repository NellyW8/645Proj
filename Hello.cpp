
#define DEBUG_TYPE "hello"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <stack>
#include <set>

using namespace llvm;



namespace {
struct Hello :  public FunctionPass
{

        /** Constructor. */
	static char ID;                           
	Hello() : FunctionPass(ID) {}

        //DEFINE_INTPASS_ANALYSIS_ADJUSTMENT(PointerAnalysisPass);

        /**
         * @brief Runs this pass on the given function.
         * @param [in,out] func The function to analyze
         * @return true if the function was modified; false otherwise
        */ virtual bool runOnFunction(llvm::Function &F);
};
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass", false, false);

bool Hello::runOnFunction(llvm::Function &F) {
    bool modified = false;
    int functionCallIndex = 1;
    for(Function::iterator block = F.begin(); block != F.end(); block++) {
        for(BasicBlock::iterator inst = block->begin(); inst != block->end();inst++) {
            Instruction * Inst = inst;
            if(isa<CallInst>(Inst) ) {
                CallInst* callInst = dyn_cast<CallInst>(Inst);
                
                Function *callee = callInst->getCalledFunction();
                ValueToValueMapTy VMap;
                if(!callee || callee->isDeclaration()) {
                    continue;
                }
                std::set<int> constantArgs;
                Function::arg_iterator arg = callee->arg_begin();
                std::vector<Value*> Args;
                errs() << "inst: " << *inst << "\n";
                errs() << "callee" << *callee;
                errs() <<"number of args is: " << callInst->getNumArgOperands() << "\n";
                for (unsigned int i = 0; i < callInst->getNumArgOperands(); ++i) {
                	errs() << "here" << "\n";
                	Value* number = callInst->getArgOperand(i);
                	errs() << "number" << *number<< "\n";
                    if(isa<Constant>(number)) {
                        errs() << "constant argument index is: " << i << "\n";
                        constantArgs.insert(i);
                        Constant *temp = cast<Constant>(callInst->getArgOperand(i));
                        VMap[arg] = temp;
                    }
                    else{
                        errs() << "copy argument index: " << i << "\n";
                        Args.push_back(callInst->getArgOperand(i));
                    }
                    arg++;
                }
                errs() << Args.size() << "\n";


                if(!constantArgs.empty() && !callee->isDeclaration()) {
                    // Clone function
                    errs() << "here2" << "\n";
                    Function* duplicateFunction = CloneFunction(callee, VMap, false);

                    duplicateFunction->setLinkage(GlobalValue::InternalLinkage);
                    callee->getParent()->getFunctionList().push_back(duplicateFunction);
                    Instruction * New;
                    New = CallInst::Create(duplicateFunction, Args, "", Inst);
                    cast<CallInst>(New)->setCallingConv(callee->getCallingConv());
                    cast<CallInst>(New)->setAttributes(callee->getAttributes());
                    if(callInst->isTailCall())cast<CallInst>(New)->setTailCall();
                    New->setDebugLoc(Inst->getDebugLoc());	
                    New->takeName(Inst);
                    Args.clear();
                    ReplaceInstWithInst(inst->getParent()->getInstList(), inst, cast<CallInst>(New));
                   
                    modified = true;
                }
                errs() << "end of a call\n";
            }
        }
    }
    return modified;
}


