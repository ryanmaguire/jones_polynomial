# CMakeList.txt : CMake project for Kauffman_Implementation, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Kauffman_Implementation "kauffman_implementation.h" "print_polynomial.c" "main.c"  "make_knot.c" "initialize_polynomial.c" "make_crossing.c"     "adjust_polynomial_degree.c"  "kauffman_polynomial.c" "make_tangle.c" "make_kauffman_summand.c" "insert_boundary_point.c" "copy_tangle.c" "delete_boundary_point.c" "copy_kauffman_summand.c"  "crossing_position.c" "pair_strands.c" "swap_strand_pairs.c" "remove_twist.c" "remove_circle.c" "add_crossing.c" "smooth_crossing.c" "catalan.c" "tangle_index.c"        "add_to_kauffman_summand.c" "add_to_kauffman_summand_collection.c"    "jones_polynomial.c" "safe_malloc.c" "safe_calloc.c" "safe_free.c" "is_crossing_consecutive.c" "make_stack.c" "push_stack.c" "pop_stack.c" "peek_stack.c" "catalan_info.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Kauffman_Implementation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
