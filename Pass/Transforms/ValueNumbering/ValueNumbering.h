#ifndef LLVM_TRANSFORMS_VALUENUMBERING_H
#define LLVM_TRANSFORMS_VALUENUMBERING_H
#include "llvm/IR/PassManager.h"
#include <string>
namespace llvm {

class ValueNumberingPass : public PassInfoMixin<ValueNumberingPass> {
	public :
	std::string func_name;
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
		
}; 

}
#endif
