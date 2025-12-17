#Produce a TransactionEventV1DTO object (or dict) that is guaranteed well-formed

import json
import sys

file_path = 'data.json'

# list of spec tuples as the source of truth in deterministic order matching the V1 schema (field, expected_type, required)

validation_fields = [
    # Domain Payload
    ('account_id', str, True),
    ('external_transaction_id', str, False),
    ('amount_minor', int, True),
    ('precision', int, True),
    ('currency', str, True),
    ('raw_description', str, False),
    ('occurred_at', str, True),
    # Log Metadata
    ('event_id', str, True),
    ('schema_version', int, True),
    ('source', str, True),
    ('source_connector', str, False),
    ('source_institution', str, False),
    ('ingested_at', str, True),
    ('batch_id', str, False),
    ('source_file_hash', str, False)
]

try:
    with open(file_path, 'r') as file:
        data = json.load(file)

    if not isinstance(data, dict):
        raise ValueError(f"{type(data)} is not in hash/dictionary format.")

    error_list = []
    event_payload = {}

    for field, expected_type, required in validation_fields:
        if required:
            if field not in data:
                error_list.append(field + ": required field missing")
                continue
            elif data[field] is None:
                error_list.append(field + ": required field is null")
                continue
        else:
            if field not in data or data[field] is None:
                event_payload[field] = None
                continue
        # boolean masquerading as int check
        if expected_type is int and isinstance(data[field], bool):
            error_list.append(field + ": invalid value type")
        elif not isinstance(data[field], expected_type):
            error_list.append(field + ": invalid value type")
        else:
            event_payload[field] = data[field]

    # initial error check to stop execution if any fields are missing or wrong type at runtime
    if error_list:
        raise ValueError(f"Schema Validation Failed\n{'\n'.join(error_list)}")

    ordered_arguments = []

    for field, expected_type, required in validation_fields:
        ordered_arguments.append(event_payload[field])




except FileNotFoundError:
    print(f"Error: The file {file_path} was not found.")
    sys.exit(1)
except json.JSONDecodeError as e:
    print(f"Error: Failed to decode JSON from the file. Details: {e}")
    sys.exit(1)
except ValueError as e:
    print(e)
    sys.exit(1)