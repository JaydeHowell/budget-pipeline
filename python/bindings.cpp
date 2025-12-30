#include <pybind11/pybind11.h>

#include "engine/engine.h"

namespace py = pybind11;

PYBIND11_MODULE(budget_pipeline_native, m) {
    m.doc() = "Budget pipeline native module";

    py::class_<pipeline::Engine>(m, "Engine")
    .def(py::init())
    .def("ingest_event",
        [](pipeline::Engine& self, py::dict event_dict) {
            auto event = event_dict.cast<event_model::TransactionEventV1>();
            self.ingest(event);
        },
        "ingest a single event into the pipeline")

    .def("ingest_batch",
        [](pipeline::Engine& self, py::list events_list) {
            auto events = events_list.cast<std::vector<event_model::TransactionEventV1>>();
            self.ingest_batch(events);
        },
        "ingest batch into the budget pipeline")

    .def("snapshot",
        [](const pipeline::Engine& self) {
            const auto snap = self.snapshot();
            py::dict d;
            d["event_count"] = snap.event_count;
            d["sum_amount_minor"] = snap.sum_amount_minor;
            d["duplicate_event_count"] = snap.duplicate_event_count;
            return d;
        },
        "return a snapshot of the engine state");
}