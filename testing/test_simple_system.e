note
	description: "Tests for SIMPLE_SYSTEM library"
	testing: "type/manual"

class
	TEST_SIMPLE_SYSTEM

inherit
	TEST_SET_BASE

feature -- Test routines

	test_computer_name
			-- Test getting computer name.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_string_not_empty ("computer_name_not_empty", l_sys.computer_name)
		end

	test_user_name
			-- Test getting user name.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_string_not_empty ("user_name_not_empty", l_sys.user_name)
		end

	test_windows_directory
			-- Test getting Windows directory.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_string_not_empty ("windows_dir_not_empty", l_sys.windows_directory)
			assert_string_contains ("contains_windows", l_sys.windows_directory.as_lower, "windows")
		end

	test_system_directory
			-- Test getting system directory.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_string_not_empty ("system_dir_not_empty", l_sys.system_directory)
			assert_string_contains ("contains_system32", l_sys.system_directory.as_lower, "system32")
		end

	test_temp_directory
			-- Test getting temp directory.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_string_not_empty ("temp_dir_not_empty", l_sys.temp_directory)
		end

	test_processor_count
			-- Test getting processor count.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_greater_or_equal ("at_least_1_processor", l_sys.processor_count, 1)
		end

	test_processor_architecture
			-- Test getting processor architecture.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_string_not_empty ("arch_not_empty", l_sys.processor_architecture)
		end

	test_page_size
			-- Test getting page size.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_greater_than ("page_size_positive", l_sys.page_size, 0)
		end

	test_total_memory
			-- Test getting total memory.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_true ("total_memory_positive", l_sys.total_memory_mb > 0)
			assert_true ("at_least_1gb", l_sys.total_memory_mb >= 1024)
		end

	test_available_memory
			-- Test getting available memory.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_true ("available_memory_positive", l_sys.available_memory_mb > 0)
			assert_true ("available_le_total", l_sys.available_memory_mb <= l_sys.total_memory_mb)
		end

	test_os_version
			-- Test getting OS version.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			assert_greater_than ("major_version_positive", l_sys.os_major_version, 0)
			assert_greater_than ("build_number_positive", l_sys.os_build_number, 0)
			assert_string_not_empty ("version_string_not_empty", l_sys.os_version_string)
		end

	test_is_64_bit
			-- Test 64-bit detection.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			-- Just verify it returns a boolean without crashing
			if l_sys.is_64_bit then
				assert_true ("64bit_has_64bit_arch", l_sys.processor_architecture.same_string ("x64") or l_sys.processor_architecture.same_string ("ARM64"))
			else
				assert_true ("32bit_has_x86_arch", l_sys.processor_architecture.same_string ("x86"))
			end
		end

	test_is_windows_10_or_later
			-- Test Windows 10+ detection.
		local
			l_sys: SIMPLE_SYSTEM
		do
			create l_sys
			-- Modern systems should be Win10+
			assert_true ("is_windows_10_or_later", l_sys.is_windows_10_or_later)
		end

end
