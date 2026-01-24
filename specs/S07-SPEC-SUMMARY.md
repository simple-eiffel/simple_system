# S07-SPEC-SUMMARY: simple_system

**BACKWASH** | Date: 2026-01-23

## Executive Summary

**simple_system** provides Windows system information for Eiffel applications:

1. **Identity**: Computer name, user name
2. **Paths**: Windows, System32, Temp directories
3. **Hardware**: CPU count, architecture, memory
4. **Software**: OS version, Windows 10/11 detection

## Architecture Overview

```
+--------------------------------+
|        SIMPLE_SYSTEM           |
+--------------------------------+
| + computer_name: STRING_32     |
| + user_name: STRING_32         |
| + windows_directory: STRING_32 |
| + system_directory: STRING_32  |
| + temp_directory: STRING_32    |
| + processor_count: INTEGER     |
| + processor_architecture: ...  |
| + is_64_bit: BOOLEAN           |
| + total_memory_mb: NATURAL_64  |
| + available_memory_mb: ...     |
| + os_version_string: STRING_32 |
| + is_windows_11: BOOLEAN       |
+--------------------------------+
              |
              v
+--------------------------------+
|       simple_system.h          |
|   (Win32 API wrappers)         |
+--------------------------------+
              |
              v
+--------------------------------+
| kernel32.dll | ntdll.dll       |
+--------------------------------+
```

## Key Design Decisions

1. **Single Class**: All system info in one place
2. **Query-Only**: No system modifications
3. **No Caching**: Fresh values always
4. **SCOOP Ready**: Thread-safe design
5. **Inline C**: No external DLLs beyond Windows

## Status

- **Phase**: 4 (Documentation)
- **Stability**: High
- **Platform**: Windows only
- **SCOOP**: Compatible
