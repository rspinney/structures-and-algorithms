cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set the project name
project(structures_and_algorithms  VERSION 0.1 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#compiler flags
if (MSVC)
	SET(CMAKE_CXX_FLAGS_RELEASE "/O2")
	SET(CMAKE_C_FLAGS_RELEASE "/O2")
elseif(APPLE) #assuming clang
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -march=native")
	set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "-flto=full -O2 -Wall -Wextra -Wpedantic -ftree-vectorize -march=native")
	SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
else() #assuing gcc
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -march=native")
	set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "-flto -O2 -Wall -Wextra -Wpedantic -ftree-vectorize -msse2 -mfpmath=sse -march=native")
	SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")	
endif()
       
#arrays

#arrays reverse
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/arrays/reverse)

add_executable(array_reverse ./src/algorithms/arrays/reverse/reverse.cpp)
set_target_properties(array_reverse PROPERTIES OUTPUT_NAME reverse)

#arrays search
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/arrays/search)

add_executable(array_linear_search ./src/algorithms/arrays/search/linear_search.cpp)
set_target_properties(array_linear_search PROPERTIES OUTPUT_NAME linear_search)

add_executable(binary_search_iterative ./src/algorithms/arrays/search/binary_search_iterative.cpp)

add_executable(binary_search_recursive ./src/algorithms/arrays/search/binary_search_recursive.cpp)

add_executable(array_quick_select ./src/algorithms/arrays/search/quick_select.cpp)
set_target_properties(array_quick_select PROPERTIES OUTPUT_NAME quick_select)
target_include_directories(array_quick_select  PRIVATE ./src/utilities/random ./src/utilities/comparators)

#array sort

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/arrays/sort)

add_executable(array_insertion_sort ./src/algorithms/arrays/sort/insertion_sort.cpp)
set_target_properties(array_insertion_sort PROPERTIES OUTPUT_NAME insertion_sort)
target_include_directories(array_insertion_sort  PRIVATE ./src/utilities/random ./src/utilities/comparators)

add_executable(array_quick_sort ./src/algorithms/arrays/sort/quick_sort.cpp)
set_target_properties(array_quick_sort PROPERTIES OUTPUT_NAME quick_sort)
target_include_directories(array_quick_sort  PRIVATE ./src/utilities/random ./src/utilities/comparators)

add_executable(array_bubble_sort ./src/algorithms/arrays/sort/bubble_sort.cpp)
set_target_properties(array_bubble_sort PROPERTIES OUTPUT_NAME bubble_sort)
target_include_directories(array_bubble_sort  PRIVATE ./src/utilities/random ./src/utilities/comparators)

add_executable(array_merge_sort ./src/algorithms/arrays/sort/merge_sort.cpp)
set_target_properties(array_merge_sort PROPERTIES OUTPUT_NAME merge_sort)
target_include_directories(array_merge_sort  PRIVATE ./src/utilities/random ./src/utilities/comparators)

add_executable(array_heap_sort ./src/algorithms/arrays/sort/heap_sort.cpp)
set_target_properties(array_heap_sort PROPERTIES OUTPUT_NAME heap_sort)
target_include_directories(array_heap_sort  PRIVATE ./src/structures/heaps/ ./src/utilities/random ./src/utilities/comparators)

add_executable(array_selection_sort ./src/algorithms/arrays/sort/selection_sort.cpp)
set_target_properties(array_selection_sort PROPERTIES OUTPUT_NAME selection_sort)
target_include_directories(array_selection_sort  PRIVATE ./src/utilities/random ./src/utilities/comparators)

#trees

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/trees)

add_executable(binary_tree ./src/structures/trees/binary_tree.cpp)
target_include_directories(binary_tree  PRIVATE ./src/structures/trees/ ./src/utilities/random)

#tree print

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/trees/print_in_order)

add_executable(tree_print_inorder ./src/algorithms/trees/print_in_order/binary_tree_print_in_order.cpp)
set_target_properties(tree_print_inorder PROPERTIES OUTPUT_NAME print_inorder)
target_include_directories(tree_print_inorder  PRIVATE ./src/structures/trees/ ./src/utilities/random)

#tree reverse

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/trees/reverse)

add_executable(tree_reverse ./src/algorithms/trees/reverse/reverse.cpp)
set_target_properties(tree_reverse PROPERTIES OUTPUT_NAME reverse)
target_include_directories(tree_reverse  PRIVATE ./src/structures/trees/ ./src/utilities/random)

#trees search

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/trees/search)

add_executable(tree_dfs_recursive ./src/algorithms/trees/search/depth_first_search_recursive.cpp)
set_target_properties(tree_dfs_recursive PROPERTIES OUTPUT_NAME dfs_recursive)
target_include_directories(tree_dfs_recursive  PRIVATE ./src/structures/trees/ ./src/utilities/random)

add_executable(tree_dfs_iterative ./src/algorithms/trees/search/depth_first_search_iterative.cpp)
set_target_properties(tree_dfs_iterative PROPERTIES OUTPUT_NAME dfs_iterative)
target_include_directories(tree_dfs_iterative  PRIVATE ./src/structures/trees/ ./src/utilities/random)

add_executable(tree_bfs_iterative ./src/algorithms/trees/search/breadth_first_search_iterative.cpp)
set_target_properties(tree_bfs_iterative PROPERTIES OUTPUT_NAME bfs_iterative)
target_include_directories(tree_bfs_iterative  PRIVATE ./src/structures/trees/ ./src/utilities/random)

add_executable(tree_bfs_recursive ./src/algorithms/trees/search/breadth_first_search_recursive.cpp)
set_target_properties(tree_bfs_recursive PROPERTIES OUTPUT_NAME bfs_recursive)
target_include_directories(tree_bfs_recursive  PRIVATE ./src/structures/trees/ ./src/utilities/random)

#graphs

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/graphs)

add_executable(graph ./src/structures/graphs/graph.cpp)
target_include_directories(graph  PRIVATE ./src/structures/structures/graphs/ ./src/utilities/random)

#graph cluster

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/graphs/cluster)

add_executable(graph_clusters ./src/algorithms/graphs/cluster/cluster_dfs_iterative.cpp)
set_target_properties(graph_clusters PROPERTIES OUTPUT_NAME clusters)
target_include_directories(graph_clusters  PRIVATE ./src/structures/graphs/ ./src/utilities/random)

#graph search

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/graphs/search)

add_executable(graph_dfs_recursive ./src/algorithms/graphs/search/depth_first_search_recursive.cpp)
set_target_properties(graph_dfs_recursive PROPERTIES OUTPUT_NAME dfs_recursive)
target_include_directories(graph_dfs_recursive  PRIVATE ./src/structures/graphs/ ./src/utilities/random)

add_executable(graph_dfs_iterative ./src/algorithms/graphs/search/depth_first_search_iterative.cpp)
set_target_properties(graph_dfs_iterative PROPERTIES OUTPUT_NAME dfs_iterative)
target_include_directories(graph_dfs_iterative  PRIVATE ./src/structures/graphs/ ./src/utilities/random)

add_executable(graph_bfs_iterative ./src/algorithms/graphs/search/breadth_first_search_iterative.cpp)
set_target_properties(graph_bfs_iterative PROPERTIES OUTPUT_NAME bfs_iterative)
target_include_directories(graph_bfs_iterative  PRIVATE ./src/structures/graphs/ ./src/utilities/random)

add_executable(graph_bfs_recursive ./src/algorithms/graphs/search/breadth_first_search_recursive.cpp)
set_target_properties(graph_bfs_recursive PROPERTIES OUTPUT_NAME bfs_recursive)
target_include_directories(graph_bfs_recursive  PRIVATE ./src/structures/graphs/ ./src/utilities/random)

#graph pathfinding

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/graphs/pathfinding)

add_executable(dijkstra ./src/algorithms/graphs/pathfinding/dijkstra.cpp)
set_target_properties(dijkstra PROPERTIES OUTPUT_NAME dijkstra)
target_include_directories(dijkstra  PRIVATE ./src/structures/graphs/ ./src/structures/heaps/ ./src/utilities/random ./src/utilities/comparators)

#lists

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/lists)

add_executable(list ./src/structures/lists/list.cpp)
target_include_directories(list  PRIVATE ./src/structures/lists/ ./src/utilities/random)

#lists sort


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/lists/sort)

add_executable(list_insertion_sort ./src/algorithms/lists/sort/insertion_sort.cpp)
set_target_properties(list_insertion_sort PROPERTIES OUTPUT_NAME insertion_sort)
target_include_directories(list_insertion_sort PRIVATE ./src/structures/lists/ ./src/utilities/random ./src/utilities/comparators)

add_executable(list_quick_sort ./src/algorithms/lists/sort/quick_sort.cpp)
set_target_properties(list_quick_sort PROPERTIES OUTPUT_NAME quick_sort)
target_include_directories(list_quick_sort PRIVATE ./src/structures/lists/ ./src/utilities/random ./src/utilities/comparators)

add_executable(list_bubble_sort ./src/algorithms/lists/sort/bubble_sort.cpp)
set_target_properties(list_bubble_sort PROPERTIES OUTPUT_NAME bubble_sort)
target_include_directories(list_bubble_sort PRIVATE ./src/structures/lists/ ./src/utilities/random ./src/utilities/comparators)

add_executable(list_merge_sort ./src/algorithms/lists/sort/merge_sort.cpp)
set_target_properties(list_merge_sort PROPERTIES OUTPUT_NAME merge_sort)
target_include_directories(list_merge_sort PRIVATE ./src/structures/lists/ ./src/utilities/random ./src/utilities/comparators)

add_executable(list_selection_sort ./src/algorithms/lists/sort/selection_sort.cpp)
set_target_properties(list_selection_sort PROPERTIES OUTPUT_NAME selection_sort)
target_include_directories(list_selection_sort PRIVATE ./src/structures/lists/ ./src/utilities/random ./src/utilities/comparators)

#list reverse

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/lists/reverse)

add_executable(reverse_list ./src/algorithms/lists/reverse/reverse_list.cpp)
target_include_directories(reverse_list  PRIVATE ./src/structures/lists/ ./src/utilities/random)

#heaps

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/heaps)

add_executable(heap ./src/structures/heaps/heap.cpp)
set_target_properties(heap PROPERTIES OUTPUT_NAME heap)
target_include_directories(heap  PRIVATE ./src/structures/heaps/ ./src/utilities/random ./src/utilities/comparators)

add_executable(indexedheap ./src/structures/heaps/indexedheap.cpp)
set_target_properties(indexedheap PROPERTIES OUTPUT_NAME indexedheap)
target_include_directories(indexedheap  PRIVATE ./src/structures/heaps/ ./src/utilities/random ./src/utilities/comparators)

#stacks

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/stack)

add_executable(stack ./src/structures/stack/stack.cpp)
set_target_properties(stack PROPERTIES OUTPUT_NAME stack)
target_include_directories(stack  PRIVATE ./src/structures/stack/)

#queues

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/queues)

add_executable(queue ./src/structures/queues/queue.cpp)
set_target_properties(queue PROPERTIES OUTPUT_NAME queue)
target_include_directories(queue  PRIVATE ./src/structures/queue/)

add_executable(queuecirc ./src/structures/queues/queue_circ.cpp)
set_target_properties(queuecirc PROPERTIES OUTPUT_NAME queuecirc)
target_include_directories(queuecirc  PRIVATE ./src/structures/queue/)

#hastable

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/structures/hashtable)

add_executable(hashtable ./src/structures/hashtable/hashtable.cpp)
set_target_properties(hashtable PROPERTIES OUTPUT_NAME hashtable)
target_include_directories(hashtable  PRIVATE ./src/structures/hashtable/)

#questions

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/questions)

add_executable(fizzbuzz ./src/questions/fizzbuzz.cpp)
set_target_properties(fizzbuzz PROPERTIES OUTPUT_NAME fizzbuzz)

add_executable(num_tests_pigs ./src/questions/num_tests_pigs.cpp)
set_target_properties(num_tests_pigs PROPERTIES OUTPUT_NAME num_tests_pigs)

add_executable(complete_graph ./src/questions/complete_graph.cpp)
set_target_properties(complete_graph PROPERTIES OUTPUT_NAME complete_graph)

add_executable(circular_array_loop ./src/questions/circular_array_loop.cpp)
set_target_properties(circular_array_loop PROPERTIES OUTPUT_NAME circular_array_loop)

add_executable(circular_array_shift ./src/questions/circular_array_shift.cpp)
set_target_properties(circular_array_shift PROPERTIES OUTPUT_NAME circular_array_shift)

add_executable(k_reverse_list ./src/questions/k_reverse_list.cpp)
set_target_properties(k_reverse_list PROPERTIES OUTPUT_NAME k_reverse_list)

add_executable(divide_ints ./src/questions/divide_ints.cpp)
set_target_properties(divide_ints PROPERTIES OUTPUT_NAME divide_ints)

add_executable(next_permutation ./src/questions/next_permutation.cpp)
set_target_properties(next_permutation PROPERTIES OUTPUT_NAME next_permutation)

add_executable(remove_duplicates_sorted_array ./src/questions/remove_duplicates_sorted_array.cpp)
set_target_properties(remove_duplicates_sorted_array PROPERTIES OUTPUT_NAME remove_duplicates_sorted_array)

add_executable(find_permutations_in_string ./src/questions/find_permutations_in_string.cpp)
set_target_properties(find_permutations_in_string PROPERTIES OUTPUT_NAME find_permutations_in_string)

add_executable(longest_valid_parentheses ./src/questions/longest_valid_parentheses.cpp)
set_target_properties(longest_valid_parentheses PROPERTIES OUTPUT_NAME longest_valid_parentheses)

###algorithms/tasks

##dynamic programming

#largest subarray / Kadanes algorithm

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/dynamic_programming/largest_subarray_kadane/)

add_executable(largestsubarray ./src/algorithms/dynamic_programming/largest_subarray_kadane/largest_subarray.cpp)
set_target_properties(largestsubarray PROPERTIES OUTPUT_NAME largestsubarray)
target_include_directories(largestsubarray  PRIVATE ./src/utilities/random)

##backtracking

#sudoku

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/algorithms/backtracking/sudoku)

add_executable(sudoku ./src/algorithms/backtracking/sudoku/sudoku.cpp)
set_target_properties(sudoku PROPERTIES OUTPUT_NAME sudoku)
target_include_directories(sudoku  PRIVATE ./src/utilities/random)

add_executable(killersudoku ./src/algorithms/backtracking/sudoku/killersudoku.cpp)
set_target_properties(killersudoku PROPERTIES OUTPUT_NAME killersudoku)
target_include_directories(killersudoku  PRIVATE ./src/utilities/random)

#target_include_directories(${EXEC_NAME}  PRIVATE ./src)
#target_include_directories(${EXEC_NAME}  SYSTEM PRIVATE ./vendor/armadillo ./vendor) #SYSTEM keyword suppresses warnings from this files

if (MSVC)
	include(CheckIPOSupported)
	check_ipo_supported(RESULT supported OUTPUT error)
	if( supported )
	    message(STATUS "IPO / LTO enabled")
	    set_property(TARGET ${EXEC_NAME}  PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
	else()
	    message(STATUS "IPO / LTO not supported: <${error}>")
	endif()
	option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
elseif (APPLE)
	set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS_RELEASE -flto=full)
else()
	set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS_RELEASE -flto)
endif()

#find_package(Threads REQUIRED)
#target_link_libraries(${EXEC_NAME} PUBLIC Threads::Threads)

