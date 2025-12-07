/*
 * simple_system.c - System information access for Eiffel
 * Copyright (c) 2025 Larry Rix - MIT License
 */

#include "simple_system.h"
#include <stdlib.h>
#include <string.h>

char* ss_get_computer_name(void) {
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(buffer);
    char* result;

    if (!GetComputerNameA(buffer, &size)) {
        return NULL;
    }

    result = (char*)malloc(size + 1);
    if (result) {
        strcpy(result, buffer);
    }
    return result;
}

char* ss_get_user_name(void) {
    char buffer[256];
    DWORD size = sizeof(buffer);
    char* result;

    if (!GetUserNameA(buffer, &size)) {
        return NULL;
    }

    result = (char*)malloc(size + 1);
    if (result) {
        strcpy(result, buffer);
    }
    return result;
}

char* ss_get_windows_directory(void) {
    char buffer[MAX_PATH];
    UINT len;
    char* result;

    len = GetWindowsDirectoryA(buffer, MAX_PATH);
    if (len == 0 || len > MAX_PATH) {
        return NULL;
    }

    result = (char*)malloc(len + 1);
    if (result) {
        strcpy(result, buffer);
    }
    return result;
}

char* ss_get_system_directory(void) {
    char buffer[MAX_PATH];
    UINT len;
    char* result;

    len = GetSystemDirectoryA(buffer, MAX_PATH);
    if (len == 0 || len > MAX_PATH) {
        return NULL;
    }

    result = (char*)malloc(len + 1);
    if (result) {
        strcpy(result, buffer);
    }
    return result;
}

char* ss_get_temp_path(void) {
    char buffer[MAX_PATH];
    DWORD len;
    char* result;

    len = GetTempPathA(MAX_PATH, buffer);
    if (len == 0 || len > MAX_PATH) {
        return NULL;
    }

    result = (char*)malloc(len + 1);
    if (result) {
        strcpy(result, buffer);
    }
    return result;
}

int ss_get_processor_count(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (int)si.dwNumberOfProcessors;
}

int ss_get_processor_architecture(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    switch (si.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_INTEL: return 0;   /* x86 */
        case PROCESSOR_ARCHITECTURE_AMD64: return 9;   /* x64 */
        case PROCESSOR_ARCHITECTURE_ARM64: return 12;  /* ARM64 */
        default: return -1;
    }
}

int ss_get_page_size(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (int)si.dwPageSize;
}

unsigned long long ss_get_total_memory_mb(void) {
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    if (!GlobalMemoryStatusEx(&ms)) {
        return 0;
    }
    return ms.ullTotalPhys / (1024 * 1024);
}

unsigned long long ss_get_available_memory_mb(void) {
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    if (!GlobalMemoryStatusEx(&ms)) {
        return 0;
    }
    return ms.ullAvailPhys / (1024 * 1024);
}

/* Use RtlGetVersion for accurate OS version (GetVersionEx is deprecated/lies) */
typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

static RTL_OSVERSIONINFOW* get_os_version_info(void) {
    static RTL_OSVERSIONINFOW osvi = {0};
    static int initialized = 0;

    if (!initialized) {
        HMODULE ntdll = GetModuleHandleA("ntdll.dll");
        if (ntdll) {
            RtlGetVersionPtr fn = (RtlGetVersionPtr)GetProcAddress(ntdll, "RtlGetVersion");
            if (fn) {
                osvi.dwOSVersionInfoSize = sizeof(osvi);
                fn(&osvi);
            }
        }
        initialized = 1;
    }
    return &osvi;
}

int ss_get_os_major_version(void) {
    return (int)get_os_version_info()->dwMajorVersion;
}

int ss_get_os_minor_version(void) {
    return (int)get_os_version_info()->dwMinorVersion;
}

int ss_get_os_build_number(void) {
    return (int)get_os_version_info()->dwBuildNumber;
}
