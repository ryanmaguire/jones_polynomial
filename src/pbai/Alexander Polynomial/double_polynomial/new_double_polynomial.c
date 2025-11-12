#include <stdlib.h>
#include "double_polynomial.h"

/* Automatically initializes an double polynomial struct given the degree */
struct double_polynomial new_double_polynomial(const int new_degree)
{
	struct double_polynomial result;

	result.degree = new_degree;
	result.coeffs = malloc((new_degree + 1) * sizeof(double));
	
	return result;
}