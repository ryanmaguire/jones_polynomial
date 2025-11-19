# CMakeList.txt : CMake project for load_balanced, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (load_balanced "add_polynomials.c" "adjust_polynomial_degree.c" "a_and_a_inverse.h" "a_and_a_inverse_definitions.c" "a_squared_plus_a_inverse_definitions.c" "a_squared_plus_a_inverse_squared.h" "bigon_search.c" "copy_link.c" "delete_crossing.c" "delete_polynomial.c" "gamma_search.c" "initialize_polynomial.c" "jones_polynomial.c" "kauffman_bracket_polynomial.c" "load_balanced.h" "make_polynomial.c" "multiply_polynomials.c" "null_gamma.c" "null_triple.c" "print_polynomial.c" "reidemeister_move_i.c" "reidemeister_move_ii.c" "reidemeister_move_iii_search.c" "safe_calloc.c" "safe_malloc.c" "smooth_crossing.c" "triple_search.c" "writhe.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET load_balanced PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.