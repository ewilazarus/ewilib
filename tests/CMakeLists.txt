enable_testing()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	find_package(Check REQUIRED)
else (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(CHECK_INSTALL_DIR "<PATH_TO_EXE>")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} ewilib)

include_directories(. ../src)
add_executable(test_runner test_backbone.c main.c)
target_link_libraries(test_runner ${LIBS} pthread)
