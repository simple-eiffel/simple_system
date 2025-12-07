note
	description: "[
		SCOOP-compatible system information access.
		Uses direct Win32 API calls via C wrapper.
	]"
	author: "Larry Rix"
	date: "$Date$"
	revision: "$Revision$"

class
	SIMPLE_SYSTEM

feature -- Computer Information

	computer_name: STRING_32
			-- Name of the computer.
		local
			l_result: POINTER
		do
			l_result := c_ss_get_computer_name
			if l_result /= default_pointer then
				Result := pointer_to_string (l_result)
				c_free (l_result)
			else
				create Result.make_empty
			end
		end

	user_name: STRING_32
			-- Name of the current user.
		local
			l_result: POINTER
		do
			l_result := c_ss_get_user_name
			if l_result /= default_pointer then
				Result := pointer_to_string (l_result)
				c_free (l_result)
			else
				create Result.make_empty
			end
		end

feature -- Directory Information

	windows_directory: STRING_32
			-- Windows installation directory (e.g., "C:\Windows").
		local
			l_result: POINTER
		do
			l_result := c_ss_get_windows_directory
			if l_result /= default_pointer then
				Result := pointer_to_string (l_result)
				c_free (l_result)
			else
				create Result.make_empty
			end
		end

	system_directory: STRING_32
			-- System directory (e.g., "C:\Windows\System32").
		local
			l_result: POINTER
		do
			l_result := c_ss_get_system_directory
			if l_result /= default_pointer then
				Result := pointer_to_string (l_result)
				c_free (l_result)
			else
				create Result.make_empty
			end
		end

	temp_directory: STRING_32
			-- Temporary files directory.
		local
			l_result: POINTER
		do
			l_result := c_ss_get_temp_path
			if l_result /= default_pointer then
				Result := pointer_to_string (l_result)
				c_free (l_result)
			else
				create Result.make_empty
			end
		end

feature -- Processor Information

	processor_count: INTEGER
			-- Number of logical processors.
		do
			Result := c_ss_get_processor_count
		end

	processor_architecture: STRING_32
			-- Processor architecture name.
		local
			l_arch: INTEGER
		do
			l_arch := c_ss_get_processor_architecture
			inspect l_arch
			when 0 then
				Result := {STRING_32} "x86"
			when 9 then
				Result := {STRING_32} "x64"
			when 12 then
				Result := {STRING_32} "ARM64"
			else
				Result := {STRING_32} "unknown"
			end
		end

	is_64_bit: BOOLEAN
			-- Is the processor 64-bit?
		do
			Result := c_ss_get_processor_architecture = 9 or c_ss_get_processor_architecture = 12
		end

	page_size: INTEGER
			-- Memory page size in bytes.
		do
			Result := c_ss_get_page_size
		end

feature -- Memory Information

	total_memory_mb: NATURAL_64
			-- Total physical memory in megabytes.
		do
			Result := c_ss_get_total_memory_mb
		end

	available_memory_mb: NATURAL_64
			-- Available physical memory in megabytes.
		do
			Result := c_ss_get_available_memory_mb
		end

	total_memory_gb: REAL_64
			-- Total physical memory in gigabytes.
		do
			Result := total_memory_mb / 1024.0
		end

	available_memory_gb: REAL_64
			-- Available physical memory in gigabytes.
		do
			Result := available_memory_mb / 1024.0
		end

feature -- OS Information

	os_major_version: INTEGER
			-- OS major version number.
		do
			Result := c_ss_get_os_major_version
		end

	os_minor_version: INTEGER
			-- OS minor version number.
		do
			Result := c_ss_get_os_minor_version
		end

	os_build_number: INTEGER
			-- OS build number.
		do
			Result := c_ss_get_os_build_number
		end

	os_version_string: STRING_32
			-- Full OS version as string (e.g., "10.0.22631").
		do
			create Result.make (20)
			Result.append_integer (os_major_version)
			Result.append_character ('.')
			Result.append_integer (os_minor_version)
			Result.append_character ('.')
			Result.append_integer (os_build_number)
		end

	is_windows_10_or_later: BOOLEAN
			-- Is this Windows 10 or later?
		do
			Result := os_major_version >= 10
		end

	is_windows_11: BOOLEAN
			-- Is this Windows 11? (Build 22000+)
		do
			Result := os_major_version >= 10 and os_build_number >= 22000
		end

feature {NONE} -- Implementation

	pointer_to_string (a_ptr: POINTER): STRING_32
			-- Convert C string pointer to STRING_32.
		local
			l_c_string: C_STRING
		do
			create l_c_string.make_by_pointer (a_ptr)
			Result := l_c_string.string.to_string_32
		end

feature {NONE} -- C externals

	c_ss_get_computer_name: POINTER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_computer_name();"
		end

	c_ss_get_user_name: POINTER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_user_name();"
		end

	c_ss_get_windows_directory: POINTER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_windows_directory();"
		end

	c_ss_get_system_directory: POINTER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_system_directory();"
		end

	c_ss_get_temp_path: POINTER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_temp_path();"
		end

	c_ss_get_processor_count: INTEGER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_processor_count();"
		end

	c_ss_get_processor_architecture: INTEGER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_processor_architecture();"
		end

	c_ss_get_page_size: INTEGER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_page_size();"
		end

	c_ss_get_total_memory_mb: NATURAL_64
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_total_memory_mb();"
		end

	c_ss_get_available_memory_mb: NATURAL_64
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_available_memory_mb();"
		end

	c_ss_get_os_major_version: INTEGER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_os_major_version();"
		end

	c_ss_get_os_minor_version: INTEGER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_os_minor_version();"
		end

	c_ss_get_os_build_number: INTEGER
		external
			"C inline use %"simple_system.h%""
		alias
			"return ss_get_os_build_number();"
		end

	c_free (a_ptr: POINTER)
		external
			"C inline"
		alias
			"free($a_ptr);"
		end

end
