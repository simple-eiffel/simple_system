# 7S-02-STANDARDS: simple_system

**BACKWASH** | Date: 2026-01-23

## Language Standards

- **Eiffel**: ECMA-367 compliant
- **C**: C99 for Win32 API calls
- **Win32**: Windows API (kernel32.dll, ntdll.dll)

## Platform Standards

- **Target OS**: Windows 10/11
- **Architecture**: x64 (primary), x86 (supported)
- **Minimum Windows**: Windows 7 (API compatibility)

## Simple Eiffel Ecosystem Standards

- Design by Contract (DBC) on all features
- Void safety enabled
- SCOOP compatible (no global state)
- Inline C pattern for native calls
- ECF-based project configuration

## API Conventions

- Query-only class (no commands modify system)
- All features are pure queries
- Results are fresh each call (no caching)
- Strings returned as STRING_32

## Win32 API Standards

| Eiffel Feature | Win32 Function |
|----------------|----------------|
| computer_name | GetComputerNameA |
| user_name | GetUserNameA |
| windows_directory | GetWindowsDirectoryA |
| system_directory | GetSystemDirectoryA |
| temp_directory | GetTempPathA |
| processor_* | GetSystemInfo |
| memory_* | GlobalMemoryStatusEx |
| os_* | RtlGetVersion |
