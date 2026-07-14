if(POLICY CMP0167)
	cmake_policy(SET CMP0167 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(nixreg_tests
	test_main.cpp
	test_bitbuffer.cpp
	test_NixieDigitMap.cpp
)

target_link_libraries(nixreg_tests PRIVATE Boost::unit_test_framework nixreg)

add_test(NAME nixreg_tests COMMAND nixreg_tests)
