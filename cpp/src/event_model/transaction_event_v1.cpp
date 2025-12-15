#include <array>
#include <cstdint>
#include <chrono>
#include <optional>
#include <string>

using Timestamp = std::chrono::sys_time<std::chrono::nanoseconds>;
using Uuid = std::array<std::uint8_t, 16>;

enum class SourceType : std::uint8_t {
    BankCsv,
    BankApi,
    ManualEntry
};

struct TransactionEventV1 {
    // Domain payload
    Uuid account_id;
    std::optional<std::string> external_transaction_id;
    std::int64_t amount_minor;
    std::int32_t precision;
    std::array<char, 3> currency; // ISO-4217, i.e. { 'U', 'S', 'D' }
    std::optional<std::string> raw_description;
    Timestamp occurred_at;

    // Log metadata
    Uuid event_id;
    std::int32_t schema_version; // invariant: == 1
    SourceType source;
    std::optional<std::string> source_connector;
    std::optional<std::string> source_institution;
    Timestamp ingested_at;
    std::optional<Uuid> batch_id;
    std::optional<std::array<char, 64>> source_file_hash_hex; // SHA-256 hex
};