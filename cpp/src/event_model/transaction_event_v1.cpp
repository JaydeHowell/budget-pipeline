#include "event_model/transaction_event_v1.h"
#include <stdexcept>
#include <algorithm>

namespace event_model {
    TransactionEventV1::TransactionEventV1(
        Uuid account_id,
        std::optional<std::string> external_transaction_id,
        std::int64_t amount_minor,
        std::int32_t precision,
        std::array<char, 3> currency,
        std::optional<std::string> raw_description,
        Timestamp occurred_at,
        Uuid event_id,
        SourceType source,
        std::optional<std::string> source_connector,
        std::optional<std::string> source_institution,
        Timestamp ingested_at,
        std::optional<Uuid> batch_id,
        std::optional<std::array<char, 64> > source_file_hash_hex
    )
        : account_id_(account_id)
          , external_transaction_id_(std::move(external_transaction_id))
          , amount_minor_(amount_minor)
          , precision_(precision)
          , currency_(currency)
          , raw_description_(std::move(raw_description))
          , occurred_at_(occurred_at)
          , event_id_(event_id)
          , schema_version_(1)
          , source_(source)
          , source_connector_(std::move(source_connector))
          , source_institution_(std::move(source_institution))
          , ingested_at_(ingested_at)
          , batch_id_(batch_id)
          , source_file_hash_hex_(source_file_hash_hex) {
        if (occurred_at_ > ingested_at_) {
            throw std::invalid_argument("occurred_at must be <= ingested at");
        }

        for (char c: currency_) {
            if (c < 'A' || c > 'Z') {
                throw std::invalid_argument("currency must be uppercase ISO-4217");
            }
        }

        if (precision_ < 0) {
            throw std::invalid_argument("precision must be non-negative");
        }
    }
    const Uuid& TransactionEventV1::account_id() const noexcept {
        return account_id_;
    }
    std::int64_t TransactionEventV1::amount_minor() const noexcept {
        return amount_minor_;
    }
    const std::array<char, 3>& TransactionEventV1::currency() const noexcept {
        return currency_;
    }
    Timestamp TransactionEventV1::occurred_at() const noexcept {
        return occurred_at_;
    }
    Timestamp TransactionEventV1::ingested_at() const noexcept {
        return ingested_at_;
    }
    SourceType TransactionEventV1::source() const noexcept {
        return source_;
    }
}
