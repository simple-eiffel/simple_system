note
	description: "Test application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	TEST_APP

create
	make

feature -- Initialization

	make
			-- Run the tests.
		do
			create tests
			run_test (agent tests.test_computer_name, "test_computer_name")
			run_test (agent tests.test_user_name, "test_user_name")
			run_test (agent tests.test_windows_directory, "test_windows_directory")
			run_test (agent tests.test_system_directory, "test_system_directory")
			run_test (agent tests.test_temp_directory, "test_temp_directory")
			run_test (agent tests.test_processor_count, "test_processor_count")
			run_test (agent tests.test_processor_architecture, "test_processor_architecture")
			run_test (agent tests.test_page_size, "test_page_size")
			run_test (agent tests.test_total_memory, "test_total_memory")
			run_test (agent tests.test_available_memory, "test_available_memory")
			run_test (agent tests.test_os_version, "test_os_version")
			run_test (agent tests.test_is_64_bit, "test_is_64_bit")
			run_test (agent tests.test_is_windows_10_or_later, "test_is_windows_10_or_later")
			print ("%N========================%N")
			print ("Results: " + passed.out + " passed, " + failed.out + " failed%N")
		end

feature {NONE} -- Implementation

	tests: LIB_TESTS

	passed: INTEGER

	failed: INTEGER

	run_test (a_test: PROCEDURE; a_name: STRING)
			-- Run a single test and update counters.
		local
			l_retried: BOOLEAN
		do
			if not l_retried then
				a_test.call (Void)
				print ("  PASS: " + a_name + "%N")
				passed := passed + 1
			end
		rescue
			print ("  FAIL: " + a_name + "%N")
			failed := failed + 1
			l_retried := True
			retry
		end

end
