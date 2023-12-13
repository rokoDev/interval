cmake_minimum_required(VERSION ${cmake_version})

set(ProjectName ${ProjectName}_tests)
project(${ProjectName})

include(FetchContent)

FetchContent_Declare(
    googletest
	  GIT_REPOSITORY https://github.com/google/googletest.git
	  GIT_TAG b3a9ba2b8e975550799838332803d468797ae2e1)

FetchContent_Declare(
    utils
    GIT_REPOSITORY https://github.com/rokoDev/utils.git
    GIT_TAG        0f5a0276194c2b72ef289aa731afa497fb6d6f15
)

FetchContent_Declare(
    user_literals
    GIT_REPOSITORY https://github.com/rokoDev/user_literals.git
    GIT_TAG        5c62773ff93b21cc5868eb3c7377deb9a8d8ec97
)

FetchContent_MakeAvailable(googletest utils user_literals)

add_library(tests_main STATIC)
target_sources(tests_main
  PRIVATE
  src/main_tests.cpp
  )
target_link_libraries(tests_main PUBLIC gtest)
target_link_libraries(tests_main INTERFACE utils user_literals)

# If use IDE add gtest, gmock, gtest_main and gmock_main targets into deps/googletest source group
set_target_properties(gtest gmock gtest_main gmock_main PROPERTIES FOLDER deps/googletest)

# If use IDE add utils target into deps source group
set_target_properties(utils user_literals PROPERTIES FOLDER deps)

get_target_property(tests_main_sources tests_main SOURCES)
source_group(
  TREE   ${CMAKE_CURRENT_SOURCE_DIR}/src
  FILES  ${tests_main_sources}
)

if (WIN32)
	option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
	option(GTEST_DISABLE_PTHREADS "Disable uses of pthreads in gtest." ON)
  option(GTEST_FORCE_SHARED_CRT "Use shared (DLL) run-time lib even when Google Test is built as static lib." ON)
endif (WIN32)


macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} "")
  target_compile_definitions(${TESTNAME} PRIVATE $<UPPER_CASE:$<CONFIG>>)
  target_sources(${TESTNAME} PRIVATE ${ARGN})
  target_link_libraries(${TESTNAME} PRIVATE interval tests_main)
  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)

  # Create groups in the IDE which mirrors directory structure on the hard disk
  get_target_property(interval_tests_src ${TESTNAME} SOURCES)
  source_group(
    TREE   ${CMAKE_CURRENT_SOURCE_DIR}#/src
    FILES  ${interval_tests_src}
  )
  # If colours in googletest are not disabled then in some versions of commandline tools which is used in Xcode 13.3 this
  # can lead to output with escape sequences. Because of that its better to disable colours in googletest.
  set_target_properties(${TESTNAME} PROPERTIES XCODE_GENERATE_SCHEME ON)
  set_target_properties(${TESTNAME} PROPERTIES XCODE_SCHEME_ARGUMENTS "--gtest_color=no")
endmacro()

package_add_test(${ProjectName}
	src/interval_tests.cpp
	)
