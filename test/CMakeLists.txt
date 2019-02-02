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
    ${INCLUDE_DIRS}/args_parser.h
    ${INCLUDE_DIRS}/map_transform.h
    ${INCLUDE_DIRS}/word_count_app.h)

# Target test list
# @TODO: Use loop to add all test files automatically
add_executable (LetterTypeTest letter_type_test.cpp ${HEADER_FILES})
target_link_libraries(LetterTypeTest gtest gmock_main libwords)
target_include_directories(LetterTypeTest PRIVATE ${INCLUDE_DIRS})
add_test(NAME LetterTypeTest COMMAND LetterTypeTest)

add_executable (ArgsParserTest args_parser_test.cpp ${HEADER_FILES})
target_link_libraries(ArgsParserTest gtest gmock_main libwords)
target_include_directories(ArgsParserTest PRIVATE ${INCLUDE_DIRS})
add_test(NAME ArgsParserTest COMMAND ArgsParserTest)

add_executable (MapTransformTest map_transform_test.cpp ${HEADER_FILES})
target_link_libraries(MapTransformTest gtest gmock_main libwords)
target_include_directories(MapTransformTest PRIVATE ${INCLUDE_DIRS})
add_test(NAME MapTransformTest COMMAND MapTransformTest)

add_executable (WordAppFreqTest word_count_app_test.cpp ${HEADER_FILES})
target_link_libraries(WordAppFreqTest gtest gmock_main libwords)
target_include_directories(WordAppFreqTest PRIVATE ${INCLUDE_DIRS})
add_test(NAME WordAppFreqTest COMMAND WordAppFreqTest)