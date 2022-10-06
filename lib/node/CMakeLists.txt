# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (node ../../src/node.h ../../src/node.c)

target_link_libraries (node LINK_PUBLIC array edge)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (node PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
