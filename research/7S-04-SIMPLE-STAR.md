# 7S-04-SIMPLE-STAR: simple_system


**Date**: 2026-01-23

**BACKWASH** | Date: 2026-01-23

## Ecosystem Integration

### Dependencies (Incoming)
- **EiffelBase**: Core types (STRING_32, C_STRING)
- **Win32 API**: kernel32.dll, ntdll.dll (system)

### Dependents (Outgoing)
- **simple_log**: System context for log entries
- **simple_diagnostic**: System health checks
- Applications needing system adaptation

## Integration Patterns

### Basic Usage
```eiffel
sys: SIMPLE_SYSTEM

create sys
print ("Computer: " + sys.computer_name + "%N")
print ("User: " + sys.user_name + "%N")
print ("CPUs: " + sys.processor_count.out + "%N")
print ("RAM: " + sys.total_memory_gb.out + " GB%N")
```

### OS Detection
```eiffel
if sys.is_windows_11 then
    -- Windows 11 specific code
elseif sys.is_windows_10_or_later then
    -- Windows 10 code
end
```

### Resource Adaptation
```eiffel
if sys.available_memory_mb < 1024 then
    -- Low memory mode
end

thread_count := sys.processor_count
```

## Ecosystem Fit

- System information provider
- Diagnostic support library
- No external dependencies beyond Win32
