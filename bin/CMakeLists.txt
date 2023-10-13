add_executable (astar.run ../src/main.c)

target_link_libraries (astar.run LINK_PUBLIC array node graph astar)
