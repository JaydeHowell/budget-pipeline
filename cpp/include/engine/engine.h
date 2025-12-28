#pragma once

#include <unordered_set>
#include <string>
#include <vector>
#include <cstdint>
#include "transaction_event_v1.h"

namespace pipeline {
    class engine final {
    public:
        engine() = default;

        void ingest(const event_model::TransactionEventV1& event);
        void ingest_batch(const std::vector<event_model::TransactionEventV1>& events);

        struct Snapshot final {
            std::uint64_t event_count = 0;
            std::int64_t sum_amount_minor = 0;
            std::uint64_t duplicate_event_count = 0;
        };

        Snapshot snapshot() const noexcept;

    private:
        std::uint64_t event_count_ = 0;
        std::int64_t sum_amount_minor_ = 0;
        std::uint64_t duplicate_event_count_ = 0;

        std::unordered_set<
            event_model::Uuid,
            event_model::UuidHash> seen_event_ids_;
    };
}