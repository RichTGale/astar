# CMakeLists files in this project can
# refer to the root source directory of the project as ${ASTAR_SOURCE_DIR} and
# to the root binary directory of the project as ${ASTAR_BINARY_DIR}.
cmake_minimum_required (VERSION 3.20)
project (ASTAR)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (libs)
add_subdirectory (bin)
