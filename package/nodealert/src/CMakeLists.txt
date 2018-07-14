# guessed...
cmake_minimum_required(VERSION 2.6)
PROJECT(ffffmlib C)

INCLUDE(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Use shared libraries" ON)
option(RESPONDD "Enable respondd support" ON)
option(INSTALL_TESTS "Also install test binaries" OFF)

set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(CMAKE_C_FLAGS "-Os -Wall --std=c99 -g3 -Wpedantic")

INCLUDE(FindPkgConfig)
pkg_search_module(UNL REQUIRED libnl-tiny)

if(RESPONDD)
	pkg_search_module(JSON REQUIRED json-c)
endif()

add_library(alert nodealert.c respondd-alert.c)
target_link_libraries(alert uci ${UNL_LIBRARIES})
target_include_directories(alert PUBLIC ${UNL_INCLUDE_DIRS})
install(TARGETS alert
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static)

if(RESPONDD)
	add_library(respondd-alert SHARED respondd-alert.c) # FIXME make this a module
	target_link_libraries(respondd-alert alert ${JSON_LIBRARIES})
	target_include_directories(respondd-nexthop PUBLIC ${JSON_INCLUDE_DIRS})
#	install(FILES $<TARGET_FILE:respondd-nexthop>
	install(FILES respondd-alert.so
		DESTINATION lib/gluon/respondd/)
endif()


enable_testing()

add_executable(alert-test alert-test.c)
target_link_libraries(alert-test alert)
add_test(NAME alert-test COMMAND alert-test)
if(INSTALL_TESTS)
	install(TARGETS alert-test
		RUNTIME DESTINATION bin)
endif()

