# S05-CONSTRAINTS: simple_system

**BACKWASH** | Date: 2026-01-23

## Technical Constraints

### Platform Constraints
- **Windows Only**: No Linux/macOS support
- **Win32 API**: Requires kernel32.dll, ntdll.dll
- **Minimum OS**: Windows 7 (API availability)

### API Constraints
- **Read-Only**: All features are queries
- **No Caching**: Fresh values on each call
- **No Async**: Synchronous API calls

### Value Constraints
- **Processor Count**: Returns logical processors (hyperthreads counted)
- **Memory**: Values in megabytes/gigabytes as appropriate
- **OS Version**: Uses RtlGetVersion for accurate Win10+ detection

## Design Constraints

### SCOOP Compatibility
- No class-level state
- No shared resources
- Thread-safe by design

### String Handling
- Win32 returns ANSI strings
- Converted to STRING_32
- Caller owns returned strings

### Memory Management
- C-allocated strings freed after conversion
- No memory leaks from normal use

## Compatibility Constraints

### Windows Version Detection
- GetVersionEx deprecated (lies about version)
- RtlGetVersion used instead (accurate)
- Build number 22000+ = Windows 11

### Architecture Detection
- PROCESSOR_ARCHITECTURE_* constants
- 0 = x86, 9 = x64, 12 = ARM64
- Unknown values return "unknown"
