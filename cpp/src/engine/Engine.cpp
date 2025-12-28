#include "engine/Engine.h"

void Engine::ingest(const event_model::TransactionEventV1 &event) {
    const auto [iter, inserted] = seen_event_ids.insert(event.event_id);

    if (!inserted) {
        return;
    }
    ++event_count;
    sum_amount_minor += event.amount_minor;
}

void Engine::ingest_batch(const std::vector<event_model::TransactionEventV1> &events) {
    for (const auto& event : events) {
        ingest(event);
    }
}
