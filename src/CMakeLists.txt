add_library (libwords word_count_app.h letter_type.h args_parser.h map_transform.h)
# Help cmake figure out the language because of header only library
set_target_properties(libwords PROPERTIES LINKER_LANGUAGE CXX)

# Build exe as wordcount, linked with libwords
add_executable (wordcount main.cpp)
target_link_libraries (wordcount libwords)