#include "engine/engine.h"

namespace pipeline {
    void engine::ingest(const event_model::TransactionEventV1 &event) {
        const auto [iter, inserted] = seen_event_ids_.insert(event.event_id());

        if (!inserted) {
            ++duplicate_event_count_;
            return;
        }
        ++event_count_;
        sum_amount_minor_ += event.amount_minor();
    }

    void engine::ingest_batch(const std::vector<event_model::TransactionEventV1> &events) {
        for (const auto &event: events) {
            ingest(event);
        }
    }

    engine::Snapshot engine::snapshot() const noexcept {
        return engine::Snapshot{
            .event_count = event_count_,
            .sum_amount_minor = sum_amount_minor_,
            .duplicate_event_count = duplicate_event_count_
        };
    }
}
