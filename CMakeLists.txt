

cmake_minimum_required (VERSION 3.12)
project(ASTAR)



# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (lib/array)
add_subdirectory (lib/edge)
add_subdirectory (lib/node)
add_subdirectory (lib/min_heap)
add_subdirectory (lib/graph)
add_subdirectory (lib/astar)
add_subdirectory (bin)
