#ifndef BUDGET_PIPELINE_ENGINE_H
#define BUDGET_PIPELINE_ENGINE_H
#include <unordered_set>

#include "transaction_event_v1.h"

class Engine {
    public:
    size_t event_count;
    int64_t sum_amount_minor;
    std::unordered_set<std::string> seen_event_ids;
    void ingest(const event_model::TransactionEventV1& event);
    void ingest_batch(const std::vector<event_model::TransactionEventV1>& events);
};


#endif //BUDGET_PIPELINE_ENGINE_H