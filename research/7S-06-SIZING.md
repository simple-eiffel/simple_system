# 7S-06-SIZING: simple_system


**Date**: 2026-01-23

**BACKWASH** | Date: 2026-01-23

## Codebase Metrics

- **Source Files**: 3 .e files
- **Header Files**: 1 .h file
- **LOC Estimate**: ~300 lines Eiffel

## Class Breakdown

| Class | Type | LOC | Features |
|-------|------|-----|----------|
| SIMPLE_SYSTEM | Concrete | ~300 | 20+ queries |

## Feature Categories

| Category | Count | Features |
|----------|-------|----------|
| Computer Info | 2 | computer_name, user_name |
| Directories | 3 | windows_directory, system_directory, temp_directory |
| Processor | 4 | processor_count, processor_architecture, is_64_bit, page_size |
| Memory | 4 | total_memory_mb/gb, available_memory_mb/gb |
| OS Version | 5 | os_major/minor/build, os_version_string, is_windows_* |

## Performance Characteristics

| Operation | Cost | Notes |
|-----------|------|-------|
| Directory queries | Fast | Single Win32 call |
| Memory queries | Fast | GlobalMemoryStatusEx |
| CPU queries | Fast | GetSystemInfo |
| OS version | Fast | RtlGetVersion |

## Resource Usage

- **Memory**: Minimal (no caching)
- **CPU**: Negligible (simple API calls)
- **I/O**: None
