# 7S-03-SOLUTIONS: simple_system


**Date**: 2026-01-23

**BACKWASH** | Date: 2026-01-23

## Alternative Solutions Considered

### 1. EXECUTION_ENVIRONMENT
- **Pros**: Standard EiffelBase class
- **Cons**: Limited to environment variables
- **Decision**: Doesn't provide system info

### 2. WEL (Windows Eiffel Library)
- **Pros**: Comprehensive Win32 wrapper
- **Cons**: Heavyweight, GUI-focused dependency
- **Decision**: Too much for simple info queries

### 3. System environment variables
- **Pros**: Simple, no C code needed
- **Cons**: Not all info available, unreliable for some values
- **Decision**: Incomplete coverage

### 4. Direct Win32 API calls (Chosen)
- **Pros**: Direct access, complete control, lightweight
- **Cons**: Windows-only, requires inline C
- **Decision**: Best fit for comprehensive system info

## Chosen Approach

**Single class with inline C externals calling Win32 APIs**

- simple_system.h wraps Win32 calls
- Inline C eliminates DLL needs
- Pure query interface
- SCOOP-compatible design (no shared state)

## Trade-offs Accepted

- Windows-only implementation
- Inline C requires C compiler
- Some values require elevated permissions
