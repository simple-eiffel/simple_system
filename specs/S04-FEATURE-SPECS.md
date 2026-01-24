# S04-FEATURE-SPECS: simple_system

**BACKWASH** | Date: 2026-01-23

## SIMPLE_SYSTEM Features

### Computer Information

| Feature | Signature | Description |
|---------|-----------|-------------|
| computer_name | : STRING_32 | Computer network name |
| user_name | : STRING_32 | Current logged-in user |

### Directory Information

| Feature | Signature | Description |
|---------|-----------|-------------|
| windows_directory | : STRING_32 | Windows folder (C:\Windows) |
| system_directory | : STRING_32 | System32 folder |
| temp_directory | : STRING_32 | Temp folder path |

### Processor Information

| Feature | Signature | Description |
|---------|-----------|-------------|
| processor_count | : INTEGER | Logical processor count |
| processor_architecture | : STRING_32 | "x86", "x64", "ARM64", "unknown" |
| is_64_bit | : BOOLEAN | True if 64-bit processor |
| page_size | : INTEGER | Memory page size in bytes |

### Memory Information

| Feature | Signature | Description |
|---------|-----------|-------------|
| total_memory_mb | : NATURAL_64 | Total RAM in megabytes |
| available_memory_mb | : NATURAL_64 | Free RAM in megabytes |
| total_memory_gb | : REAL_64 | Total RAM in gigabytes |
| available_memory_gb | : REAL_64 | Free RAM in gigabytes |

### OS Information

| Feature | Signature | Description |
|---------|-----------|-------------|
| os_major_version | : INTEGER | Major version (10 for Win10/11) |
| os_minor_version | : INTEGER | Minor version |
| os_build_number | : INTEGER | Build number |
| os_version_string | : STRING_32 | "10.0.22631" format |
| is_windows_10_or_later | : BOOLEAN | True if Win10+ |
| is_windows_11 | : BOOLEAN | True if build >= 22000 |

## Architecture Values

| Code | processor_architecture | Description |
|------|------------------------|-------------|
| 0 | "x86" | 32-bit Intel/AMD |
| 9 | "x64" | 64-bit Intel/AMD |
| 12 | "ARM64" | 64-bit ARM |
| other | "unknown" | Unknown architecture |

## Implementation Notes

- All strings converted from C via C_STRING
- Memory values from GlobalMemoryStatusEx
- OS version from RtlGetVersion (accurate for Win10+)
