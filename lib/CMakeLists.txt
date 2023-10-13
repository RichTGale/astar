add_library (array ../../src/array.h ../../src/array.c)
add_library (edge ../../src/edge.h ../../src/edge.c)
add_library (node ../../src/node.h ../../src/node.c)
add_library (min_heap ../../src/min_heap.h ../../src/min_heap.c)
add_library (graph ../../src/graph.h ../../src/graph.c)
add_library (astar ../../src/astar.h ../../src/astar.c)

target_link_libraries(node LINK_PUBLIC array edge)
target_link_libraries(min_heap LINK_PUBLIC array)
target_link_libraries(graph LINK_PUBLIC array node)
target_link_libraries(astar LINK_PUBLIC array node graph min_heap)

target_include_directories (astar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
