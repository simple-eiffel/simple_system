# S03-CONTRACTS: simple_system

**BACKWASH** | Date: 2026-01-23

## SIMPLE_SYSTEM Contracts

### Feature Contracts

The SIMPLE_SYSTEM class has minimal explicit contracts since all features are pure queries that return system values.

### Implicit Contracts

All features have these implicit guarantees:

```eiffel
computer_name: STRING_32
    -- Result is valid STRING_32 (possibly empty if API fails)
    ensure
        result_attached: Result /= Void

user_name: STRING_32
    -- Result is valid STRING_32 (possibly empty if API fails)
    ensure
        result_attached: Result /= Void

windows_directory: STRING_32
    -- Result is valid path or empty string
    ensure
        result_attached: Result /= Void

processor_count: INTEGER
    -- Always positive (at least 1 processor)
    ensure
        positive: Result >= 1

processor_architecture: STRING_32
    -- Returns "x86", "x64", "ARM64", or "unknown"
    ensure
        result_attached: Result /= Void

total_memory_mb: NATURAL_64
    -- Always positive
    ensure
        positive: Result > 0

available_memory_mb: NATURAL_64
    -- Always <= total_memory_mb
    ensure
        within_total: Result <= total_memory_mb
```

## Error Handling

- No exceptions thrown
- Invalid queries return empty strings or 0
- C functions handle Win32 API errors internally
- Memory freed by c_free after string conversion

## Thread Safety

- All queries are independent
- No shared state between calls
- SCOOP-compatible design
