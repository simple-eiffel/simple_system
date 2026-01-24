# 7S-01-SCOPE: simple_system

**BACKWASH** | Date: 2026-01-23

## Problem Domain

Simple_system provides SCOOP-compatible access to Windows system information through inline C externals wrapping Win32 API calls.

Key capabilities:
- Computer and user identification
- Directory paths (Windows, System, Temp)
- Processor information (count, architecture, page size)
- Memory statistics (total, available)
- OS version detection

## Target Users

- Eiffel applications needing system information
- Diagnostic and monitoring tools
- Applications adapting to system capabilities
- Installers and configuration utilities

## Business Value

- Single class for all system info queries
- SCOOP-compatible design
- No external dependencies beyond Win32
- Consistent API across system attributes

## Out of Scope

- Hardware enumeration (devices, drives)
- Network configuration
- Process/thread management
- Registry access
- Performance monitoring (beyond memory)
- Linux/macOS support
