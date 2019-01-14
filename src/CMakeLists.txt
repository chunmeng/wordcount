add_library (libwords letter_type.h)
set_target_properties(libwords PROPERTIES LINKER_LANGUAGE CXX)
add_executable (wordfreq main.cpp)
target_link_libraries (wordfreq libwords)