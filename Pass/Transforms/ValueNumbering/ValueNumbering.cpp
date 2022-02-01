#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/PassManager.h"

#include "llvm/Support/raw_ostream.h"

using namespace std;

using namespace llvm;

namespace {

// This method implements what the pass does
void visitor(Function &F){

    // Here goes what you want to do with a pass
    
		string func_name = "main";
	    errs() << "ValueNumbering: " << F.getName() << "\n";
	    
	    // Comment this line
        if (F.getName() != func_name) return;
		
        for (auto& basic_block : F)
        {
            for (auto& inst : basic_block)
            {
                errs() << inst << "\n";
                if(inst.getOpcode() == Instruction::Load){
                    errs() << "This is Load"<<"\n";
                }
                if(inst.getOpcode() == Instruction::Store){
                    errs() << "This is Store"<<"\n";
                }
                if (inst.isBinaryOp())
                {
                    errs() << "Op Code:" << inst.getOpcodeName()<<"\n";
                    if(inst.getOpcode() == Instruction::Add){
                        errs() << "This is Addition"<<"\n";
                    }
                    if(inst.getOpcode() == Instruction::Load){
                        errs() << "This is Load"<<"\n";
                    }
                    if(inst.getOpcode() == Instruction::Mul){
                        errs() << "This is Multiplication"<<"\n";
                    }
                    
                    // see other classes, Instruction::Sub, Instruction::UDiv, Instruction::SDiv
                    // errs() << "Operand(0)" << (*inst.getOperand(0))<<"\n";
                    auto* ptr = dyn_cast<User>(&inst);
		    		//errs() << "\t" << *ptr << "\n";
                    for (auto it = ptr->op_begin(); it != ptr->op_end(); ++it) {
                        errs() << "\t" <<  *(*it) << "\n";
                        // if ((*it)->hasName()) 
			    		// errs() << (*it)->getName() << "\n";                      
                    }
                } // end if
            } // end for inst
        } // end for block
        
}


// New PM implementation
struct ValueNumberingPass : public PassInfoMixin<ValueNumberingPass> {

  // The first argument of the run() function defines on what level
  // of granularity your pass will run (e.g. Module, Function).
  // The second argument is the corresponding AnalysisManager
  // (e.g ModuleAnalysisManager, FunctionAnalysisManager)
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
  	visitor(F);
	return PreservedAnalyses::all();

	
  }
  
    static bool isRequired() { return true; }
};
}



//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "ValueNumberingPass", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if(Name == "value-numbering"){
            FPM.addPass(ValueNumberingPass());
            return true;
          }
          return false;
        });
    }};
}
