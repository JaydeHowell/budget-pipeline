#pragma once

#include <array>
#include <cstdint>
#include <chrono>
#include <optional>
#include <string>

namespace event_model {
    using Timestamp = std::chrono::sys_time<std::chrono::nanoseconds>;
    using Uuid = std::array<std::uint8_t, 16>;

    enum class SourceType : std::uint8_t {
        BankCsv,
        BankApi,
        ManualEntry
    };

    class TransactionEventV1 {
    public:
        TransactionEventV1(
            // Domain payload
            Uuid account_id,
            std::optional<std::string> external_transaction_id,
            std::int64_t amount_minor,
            std::int32_t precision,
            std::array<char, 3> currency, // ISO-4217, i.e. { 'U', 'S', 'D' }
            std::optional<std::string> raw_description,
            Timestamp occurred_at,

            // Log metadata
            Uuid event_id,
            SourceType source,
            std::optional<std::string> source_connector,
            std::optional<std::string> source_institution,
            Timestamp ingested_at,
            std::optional<Uuid> batch_id,
            std::optional<std::array<char, 64> > source_file_hash_hex // SHA-256 hex
    );

    [[nodiscard]] const Uuid &account_id() const noexcept;

    [[nodiscard]] std::int64_t amount_minor() const noexcept;

    const std::array<char, 3> &currency() const noexcept;

    [[nodiscard]] Timestamp occurred_at() const noexcept;

    [[nodiscard]] Timestamp ingested_at() const noexcept;

    [[nodiscard]] SourceType source() const noexcept;

    private
    :
    // Domain payload
    Uuid account_id_;
    std::optional<std::string> external_transaction_id_;
    std::int64_t amount_minor_;
    std::int32_t precision_;
    std::array<char, 3> currency_; // ISO-4217, i.e. { 'U', 'S', 'D' }
    std::optional<std::string> raw_description_;
    Timestamp occurred_at_;

    // Log metadata
    Uuid event_id_;
    std::int32_t schema_version_;
    SourceType source_;
    std::optional<std::string> source_connector_;
    std::optional<std::string> source_institution_;
    Timestamp ingested_at_;
    std::optional<Uuid> batch_id_;
    std::optional<std::array<char, 64> > source_file_hash_hex_; // SHA-256 hex
};

}
