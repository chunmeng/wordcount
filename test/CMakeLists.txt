if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(../cmake/DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             release-1.8.1
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

set(INCLUDE_DIRS ../src/)
set(HEADER_FILES
    ${INCLUDE_DIRS}/letter_type.h
    ${INCLUDE_DIRS}/args_parser.h)

# Target test list
add_executable (LetterTypeTest letter_type_test.cpp ${HEADER_FILES})
target_link_libraries(LetterTypeTest gtest gmock_main libwords)
target_include_directories(LetterTypeTest PRIVATE ${INCLUDE_DIRS})

add_executable (ArgsParserTest args_parser_test.cpp ${HEADER_FILES})
target_link_libraries(ArgsParserTest gtest gmock_main libwords)
target_include_directories(ArgsParserTest PRIVATE ${INCLUDE_DIRS})

add_test(NAME LetterTypeTest COMMAND LetterTypeTest)
add_test(NAME ArgsParserTest COMMAND ArgsParserTest)