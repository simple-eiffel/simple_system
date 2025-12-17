/*
 * simple_system.c - Cross-platform System information access for Eiffel
 *
 * Windows: Uses Win32 GetComputerName, GetSystemInfo, GlobalMemoryStatusEx
 * Linux: Uses POSIX gethostname, sysconf, sysinfo, uname
 * macOS: Uses POSIX gethostname, sysconf, sysctl, uname
 *
 * Copyright (c) 2025 Larry Rix - MIT License
 */

#include "simple_system.h"
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(EIF_WINDOWS)
/* ============ WINDOWS IMPLEMENTATION ============ */

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

#else
/* ============ POSIX IMPLEMENTATION (Linux/macOS) ============ */

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>

#ifdef __linux__
#include <sys/sysinfo.h>
#elif defined(__APPLE__)
#include <sys/sysctl.h>
#endif

char* ss_get_computer_name(void) {
    char buffer[256];
    char* result;

    if (gethostname(buffer, sizeof(buffer)) != 0) {
        return NULL;
    }

    result = strdup(buffer);
    return result;
}

char* ss_get_user_name(void) {
    struct passwd* pw;
    char* result;

    pw = getpwuid(getuid());
    if (!pw || !pw->pw_name) {
        /* Fallback to getlogin */
        const char* login = getlogin();
        if (!login) return NULL;
        return strdup(login);
    }

    result = strdup(pw->pw_name);
    return result;
}

char* ss_get_windows_directory(void) {
    /* On Unix, return "/" as the system root */
    return strdup("/");
}

char* ss_get_system_directory(void) {
    /* On Unix, return "/usr/bin" as the system binaries directory */
    return strdup("/usr/bin");
}

char* ss_get_temp_path(void) {
    const char* tmp;

    /* Check environment variables in order of preference */
    tmp = getenv("TMPDIR");
    if (tmp && tmp[0]) return strdup(tmp);

    tmp = getenv("TMP");
    if (tmp && tmp[0]) return strdup(tmp);

    tmp = getenv("TEMP");
    if (tmp && tmp[0]) return strdup(tmp);

    /* Default to /tmp */
    return strdup("/tmp");
}

int ss_get_processor_count(void) {
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    return (nprocs > 0) ? (int)nprocs : 1;
}

int ss_get_processor_architecture(void) {
    struct utsname info;

    if (uname(&info) != 0) {
        return -1;
    }

    /* Check machine type */
    if (strcmp(info.machine, "x86_64") == 0 ||
        strcmp(info.machine, "amd64") == 0) {
        return 9;  /* x64 */
    } else if (strcmp(info.machine, "i386") == 0 ||
               strcmp(info.machine, "i486") == 0 ||
               strcmp(info.machine, "i586") == 0 ||
               strcmp(info.machine, "i686") == 0) {
        return 0;  /* x86 */
    } else if (strcmp(info.machine, "aarch64") == 0 ||
               strcmp(info.machine, "arm64") == 0) {
        return 12; /* ARM64 */
    }

    return -1; /* Unknown */
}

int ss_get_page_size(void) {
    long page_size = sysconf(_SC_PAGESIZE);
    return (page_size > 0) ? (int)page_size : 4096;
}

unsigned long long ss_get_total_memory_mb(void) {
#ifdef __linux__
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        return 0;
    }
    return ((unsigned long long)info.totalram * info.mem_unit) / (1024 * 1024);
#elif defined(__APPLE__)
    int mib[2] = { CTL_HW, HW_MEMSIZE };
    uint64_t memsize = 0;
    size_t len = sizeof(memsize);
    if (sysctl(mib, 2, &memsize, &len, NULL, 0) != 0) {
        return 0;
    }
    return memsize / (1024 * 1024);
#else
    /* Fallback: use sysconf if available */
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGESIZE);
    if (pages > 0 && page_size > 0) {
        return ((unsigned long long)pages * page_size) / (1024 * 1024);
    }
    return 0;
#endif
}

unsigned long long ss_get_available_memory_mb(void) {
#ifdef __linux__
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        return 0;
    }
    return ((unsigned long long)info.freeram * info.mem_unit) / (1024 * 1024);
#elif defined(__APPLE__)
    /* macOS: use vm_statistics for free memory */
    /* For simplicity, return 0 - full implementation would use mach_host_statistics */
    return 0;
#else
    long pages = sysconf(_SC_AVPHYS_PAGES);
    long page_size = sysconf(_SC_PAGESIZE);
    if (pages > 0 && page_size > 0) {
        return ((unsigned long long)pages * page_size) / (1024 * 1024);
    }
    return 0;
#endif
}

/* Cache parsed version info */
static struct {
    int major;
    int minor;
    int patch;
    int initialized;
} os_version_cache = {0, 0, 0, 0};

static void parse_os_version(void) {
    struct utsname info;

    if (os_version_cache.initialized) return;

    if (uname(&info) == 0) {
        /* Parse release string like "5.15.0-generic" or "22.1.0" */
        sscanf(info.release, "%d.%d.%d",
               &os_version_cache.major,
               &os_version_cache.minor,
               &os_version_cache.patch);
    }

    os_version_cache.initialized = 1;
}

int ss_get_os_major_version(void) {
    parse_os_version();
    return os_version_cache.major;
}

int ss_get_os_minor_version(void) {
    parse_os_version();
    return os_version_cache.minor;
}

int ss_get_os_build_number(void) {
    parse_os_version();
    return os_version_cache.patch;
}

#endif /* _WIN32 */
