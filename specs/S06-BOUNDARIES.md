# S06-BOUNDARIES: simple_system

**BACKWASH** | Date: 2026-01-23

## System Boundaries

### External Dependencies

```
+----------------+     +------------------+     +------------+
| Application    | --> | simple_system    | --> | Win32 API  |
+----------------+     +------------------+     +------------+
                              |
                              v
                       +------------------+
                       | simple_system.h  |
                       +------------------+
```

### Win32 DLL Boundaries

```
+------------------+
| simple_system    |
+------------------+
         |
    +----+----+
    |         |
    v         v
+--------+ +--------+
|kernel32| |ntdll   |
+--------+ +--------+
```

### API Boundary

**Public API** (all queries):
- Computer/user identification
- Directory paths
- Processor information
- Memory statistics
- OS version detection

**Internal API**:
- C external functions (c_ss_*)
- Pointer to string conversion

## Data Type Boundaries

| Eiffel | C | Win32 |
|--------|---|-------|
| STRING_32 | char* | LPSTR |
| INTEGER | int | DWORD |
| NATURAL_64 | unsigned long long | ULONGLONG |
| BOOLEAN | int | BOOL |
| POINTER | void* | LPVOID |

## Responsibility Boundaries

### simple_system Responsible For:
- Eiffel-friendly API
- Type conversions
- Memory cleanup

### Win32 Responsible For:
- System information retrieval
- Thread-safe API calls
- Permission checks

### Application Responsible For:
- Error handling decisions
- Value interpretation
- Privacy considerations
