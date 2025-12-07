/*
 * simple_system.h - System information access for Eiffel
 * Copyright (c) 2025 Larry Rix - MIT License
 */

#ifndef SIMPLE_SYSTEM_H
#define SIMPLE_SYSTEM_H

#include <windows.h>

/* Get computer name. Caller must free result. */
char* ss_get_computer_name(void);

/* Get user name. Caller must free result. */
char* ss_get_user_name(void);

/* Get Windows directory (e.g., "C:\Windows"). Caller must free result. */
char* ss_get_windows_directory(void);

/* Get System directory (e.g., "C:\Windows\System32"). Caller must free result. */
char* ss_get_system_directory(void);

/* Get temp path. Caller must free result. */
char* ss_get_temp_path(void);

/* Get number of processors */
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

/* Get OS build number */
int ss_get_os_build_number(void);

#endif /* SIMPLE_SYSTEM_H */
