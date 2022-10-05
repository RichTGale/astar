# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (array)
add_subdirectory (edge)
add_subdirectory (node)
add_subdirectory (min_heap)
add_subdirectory (graph)
add_subdirectory (astar)

add_library (main ../src/main.c)

target_link_libraries (main LINK_PUBLIC array node graph astar)

target_include_directories (main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
