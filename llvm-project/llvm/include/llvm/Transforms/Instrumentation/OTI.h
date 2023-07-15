#ifndef LLVM_TRANSFORMS_INSTRUMENTATION_OTI_H
#define LLVM_TRANSFORMS_INSTRUMENTATION_OTI_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class OTIPass: public PassInfoMixin<OTIPass> {
public:
  PreservedAnalyses run(Module&, ModuleAnalysisManager&);
};

}
#endif  // LLVM_TRANSFORMS_INSTRUMENTATION_OTI_H
