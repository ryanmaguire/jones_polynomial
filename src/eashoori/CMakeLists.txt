# CMakeList.txt : CMake project for ashoori_code, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ashoori_code "main.c" "skein_template.h" "isitsmaller.c" "splice.c" "virtue.c" "free_gauss.c" "writhe.c" "Jones_Partial.c" "JONES.c" "initialize_polynomial.c" "make_polynomial.c" "add_polynomials.c" "multiply_polynomials.c" "polynomial_power.c" "adjust_polynomial_degree.c" "print_polynomial.c" "subtract_polynomials.c" "scale_polynomial.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ashoori_code PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
