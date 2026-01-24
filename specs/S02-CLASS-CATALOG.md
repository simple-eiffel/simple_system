# S02-CLASS-CATALOG: simple_system

**BACKWASH** | Date: 2026-01-23

## Classes

| Class | Type | Description |
|-------|------|-------------|
| SIMPLE_SYSTEM | Concrete | System information provider |

## SIMPLE_SYSTEM

**Purpose**: Query Windows system information

**Creation**: Default creation (no make needed)

**Feature Groups**:

### Computer Information
- computer_name: STRING_32
- user_name: STRING_32

### Directory Information
- windows_directory: STRING_32
- system_directory: STRING_32
- temp_directory: STRING_32

### Processor Information
- processor_count: INTEGER
- processor_architecture: STRING_32
- is_64_bit: BOOLEAN
- page_size: INTEGER

### Memory Information
- total_memory_mb: NATURAL_64
- available_memory_mb: NATURAL_64
- total_memory_gb: REAL_64
- available_memory_gb: REAL_64

### OS Information
- os_major_version: INTEGER
- os_minor_version: INTEGER
- os_build_number: INTEGER
- os_version_string: STRING_32
- is_windows_10_or_later: BOOLEAN
- is_windows_11: BOOLEAN

## C External Functions

| Function | Purpose |
|----------|---------|
| ss_get_computer_name | Get computer name |
| ss_get_user_name | Get logged-in user |
| ss_get_windows_directory | Windows folder path |
| ss_get_system_directory | System32 path |
| ss_get_temp_path | Temp folder path |
| ss_get_processor_count | Logical CPU count |
| ss_get_processor_architecture | CPU arch code |
| ss_get_page_size | Memory page size |
| ss_get_total_memory_mb | Total RAM MB |
| ss_get_available_memory_mb | Free RAM MB |
| ss_get_os_major_version | OS major version |
| ss_get_os_minor_version | OS minor version |
| ss_get_os_build_number | OS build number |
