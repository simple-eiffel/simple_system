/*
 * simple_system.h - Cross-platform System information access for Eiffel
 *
 * Windows: Uses Win32 GetComputerName, GetSystemInfo, GlobalMemoryStatusEx
 * Linux/macOS: Uses POSIX gethostname, sysconf, sysinfo/uname
 *
 * Copyright (c) 2025 Larry Rix - MIT License
 */

#ifndef SIMPLE_SYSTEM_H
#define SIMPLE_SYSTEM_H

#if defined(_WIN32) || defined(EIF_WINDOWS)
#include <windows.h>
#endif

/* Get computer/host name. Caller must free result. */
char* ss_get_computer_name(void);

/* Get user name. Caller must free result. */
char* ss_get_user_name(void);

/* Get system root directory.
 * Windows: "C:\Windows", Linux/macOS: "/" or "/usr"
 * Caller must free result.
 */
char* ss_get_windows_directory(void);

/* Get system binaries directory.
 * Windows: "C:\Windows\System32", Linux/macOS: "/usr/bin"
 * Caller must free result.
 */
char* ss_get_system_directory(void);

/* Get temp path. Caller must free result. */
char* ss_get_temp_path(void);

/* Get number of processors/cores */
int ss_get_processor_count(void);

/* Get processor architecture (0=x86, 9=x64, 12=ARM64, -1=unknown) */
int ss_get_processor_architecture(void);

/* Get page size in bytes */
int ss_get_page_size(void);

/* Get total physical memory in MB */
unsigned long long ss_get_total_memory_mb(void);

/* Get available physical memory in MB */
unsigned long long ss_get_available_memory_mb(void);

/* Get OS major version */
int ss_get_os_major_version(void);

/* Get OS minor version */
int ss_get_os_minor_version(void);

/* Get OS build number (Windows) or patch level (Linux kernel) */
int ss_get_os_build_number(void);

#endif /* SIMPLE_SYSTEM_H */
