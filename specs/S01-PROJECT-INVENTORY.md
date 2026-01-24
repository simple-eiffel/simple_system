# S01-PROJECT-INVENTORY: simple_system

**BACKWASH** | Date: 2026-01-23

## Project Structure

```
simple_system/
├── src/
│   ├── simple_system.e         # Main system info class
│   └── simple_system.h         # C wrapper header
├── testing/
│   ├── test_app.e              # Test application
│   └── lib_tests.e             # Test suite
├── simple_system.ecf           # Library ECF
├── research/                   # Research documents
└── specs/                      # Specification documents
```

## Key Files

| File | Purpose |
|------|---------|
| simple_system.e | System information queries |
| simple_system.h | Win32 API wrapper functions |

## Win32 API Dependencies

| API | Header | DLL |
|-----|--------|-----|
| GetComputerNameA | windows.h | kernel32.dll |
| GetUserNameA | windows.h | advapi32.dll |
| GetWindowsDirectoryA | windows.h | kernel32.dll |
| GetSystemDirectoryA | windows.h | kernel32.dll |
| GetTempPathA | windows.h | kernel32.dll |
| GetSystemInfo | windows.h | kernel32.dll |
| GlobalMemoryStatusEx | windows.h | kernel32.dll |
| RtlGetVersion | winternl.h | ntdll.dll |

## Configuration

- **ECF**: simple_system.ecf
- **Void Safety**: Complete
- **Platform**: Windows only
