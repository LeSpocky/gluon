# guessed...
cmake_minimum_required(VERSION 2.6)
project(ffffmlib C)

INCLUDE(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Use shared libraries" ON)
option(RESPONDD "Enable respondd support" ON)
option(INSTALL_TESTS "Also install test binaries" OFF)

include(FindPkgConfig)
#pkg_search_module(UNL REQUIRED libnl-tiny)
pkg_search_module(JSON REQUIRED json-c)

add_library(alert nodealert.c respondd-alert.c)
target_link_libraries(alert uci ${UNL_LIBRARIES})
target_include_directories(alert PUBLIC ${UNL_INCLUDE_DIRS})
install(TARGETS alert
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static)

add_library(alert nodealert.c)
target_link_libraries(alert uci ${JSON_LIBRARIES})
install(TARGETS alert
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static)

if(RESPONDD)
	set_target_properties(respondd-alert PROPERTIES
		PREFIX ""
	)
	target_link_libraries(respondd-alert alert ${JSON_LIBRARIES})
	target_include_directories(respondd-alert PRIVATE ${JSON_INCLUDE_DIRS})
	install(TARGETS respondd-alert
		LIBRARY DESTINATION lib/gluon/respondd/
	)
endif(RESPONDD)

enable_testing()

add_executable(alert-test alert-test.c)
target_link_libraries(alert-test alert ${JSON_LIBRARIES})

add_test(NAME alert-test COMMAND alert-test)
target_include_directories(alert-test PRIVATE ${JSON_INCLUDE_DIRS})

if(INSTALL_TESTS)
	install(TARGETS alert-test
		RUNTIME DESTINATION bin)
endif(INSTALL_TESTS)
