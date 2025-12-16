#Load JSON

#Validate required fields, types, and invariants from the schema
#expected JSON/Python runtime type (e.g., str, int)
#conversion target (e.g., UUID object, datetime object)
#invariants/range constraints

#Normalize only what the contract requires (e.g., ensure currency is uppercase, ensure hash length)

#Produce a TransactionEventV1DTO object (or dict) that is guaranteed valid

import json
import sys

file_path = 'data.json'

required_fields = {
    'account_id': str,
    'amount_minor': int,
    'precision': int,
    'currency': str,
    'occurred_at': str,
    'event_id': str,
    'schema_version': int,
    'source': str,
    'ingested_at': str
}

optional_fields = {
    'external_transaction_id': str,
    'raw_description': str,
    'source_connector': str,
    'source_institution': str,
    'batch_id': str,
    'source_file_hash': str
}

optional_variables = {}

try:
    with open(file_path, 'r') as file:
        data = json.load(file)

    if isinstance(data, dict):
        raise ValueError(f"{type(data)} is not in hash/dictionary format.")

    error_list = []
    event_payload = {}

    for key, value in required_fields.items():
        if key not in data:
            error_list.append(key + ": required field missing")
            continue
        elif data[key] is None:
            error_list.append(key + ": required field is null")
        elif value is int and isinstance(data[key], bool):
            error_list.append(key + ": invalid value type")
        elif not isinstance(data[key], value):
            error_list.append(key + ": invalid value type")
        else:
            event_payload[key] = data[key]
    for key, value in optional_fields.items():
        if key not in data or data[key] is None:
            event_payload[key] = None
        elif value is int and isinstance(data[key], bool):
            error_list.append(key + ": invalid value type")
        elif not isinstance(data[key], value):
            error_list.append(key + ": invalid value type")
        else:
            event_payload[key] = data[key]

    # initial error check to stop execution if any fields are missing or wrong type at runtime
    if error_list:
        raise ValueError(f"Schema Validation Failed\n{'\n'.join(error_list)}")


except FileNotFoundError:
    print(f"Error: The file {file_path} was not found.")
    sys.exit(1)
except json.JSONDecodeError as e:
    print(f"Error: Failed to decode JSON from the file. Details: {e}")
    sys.exit(1)
except ValueError as e:
    print(e)
    sys.exit(1)