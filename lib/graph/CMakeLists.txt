# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (graph ../../src/graph.h ../../src/graph.c)

target_link_libraries (graph LINK_PUBLIC array node)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
