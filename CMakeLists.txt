# CMakeLists files in this project can
# refer to the root source directory of the project as ${ASTAR_SOURCE_DIR} and
# to the root binary directory of the project as ${ASTAR_BINARY_DIR}.
cmake_minimum_required (VERSION 3.12)
project (ASTAR)

# Add executable called "astar.run" that is built from the source
# files "*.c" and "*.h".
file(GLOB astar_src CONFIGURE_DEPENDS "*.h" "*.c")
add_executable (astar.run ${astar_src})  
