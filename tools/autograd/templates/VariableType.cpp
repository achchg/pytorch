#include "torch/csrc/autograd/VariableTypeUtils.h"

#include <ATen/TypeDefault.h>
#include <torch/library.h>
#include <ATen/core/op_registration/hacky_wrapper_for_legacy_signatures.h>

// ${generated_comment}

// NOTE [Sharded File]: on this file's split-into-shards state
//
// Back in the good old days, VariableType.cpp was generated as one
// file with every function in it, and everything was great and
// simple.
//
// However, this file was also very large (over 36,000 lines), and
// compiling it was very slow, and in fact was a significant
// bottleneck for incremental rebuilds. To address this, we now
// generate the file split across multiple shards, named
// VariableType_0.cpp and so on, which can be compiled in parallel.
//
// For ease of inspection and debugging, so that it's not necessary to
// go rooting around in multiple files, we also generate all the
// functions together in VariableTypeEverything.cpp. This generated
// file is only for convenience; it's not actually used in the
// build. If the file you're looking at now is one of the shards, you
// may want to switch over to the Everything variant to make you
// grepping smoother.

using namespace at;
using namespace torch::autograd::generated;

namespace torch { namespace autograd {

namespace VariableType {
namespace{
  void reset_grad_accumulator(Variable & self) {
    AutogradMeta* meta = torch::autograd::impl::get_autograd_meta(self);
    if (meta != nullptr) {
      meta->grad_accumulator_.reset();
    }
  }

  // TODO The maybe_unwrap_optional_tensor is only needed because our at::native::xxx functions
  // still take "Tensor" instead of "optional<Tensor>", so we need CPUType, TypeDefault, ...
  // to do the same. Once at::native::xxx are converted, we can remove use_optional_tensor
  // and use the use_optional_tensor=True behavior always.
  template<class T, std::enable_if_t<!std::is_same<c10::optional<at::Tensor>, std::decay_t<T>>::value, int> = 0>
  decltype(auto) maybe_unwrap_optional_tensor(T&& arg) {
    return std::forward<T>(arg);
  }
  Tensor maybe_unwrap_optional_tensor(const c10::optional<at::Tensor>& arg) {
    if (arg.has_value()) {
      return *arg;
    } else {
      return Tensor();
    }
  }
}

// Comment the anonymous namespace so that the generated functions
// can be accessed from outside of the files (register_mobile_autograd.cpp).
// Later when we merge the mobile op registration the anonymous namespace
// will be restored.
// namespace {
${type_derived_method_definitions}
// }
}

namespace {

TORCH_LIBRARY_IMPL(aten, Autograd, m) {
  ${wrapper_registrations}
}

}

}} // namespace torch::autograd
