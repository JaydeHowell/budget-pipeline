#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(budget_pipeline_native, m) {
    m.doc() = "Budget pipeline native module";

    m.def()
}