#include <stdlib.h>
#include "int_polynomial.h"

/* Automatically initializes an int polynomial struct given the degree */
struct int_polynomial new_int_polynomial(const int new_degree) 
{
	struct int_polynomial result;

	result.degree = new_degree;
	result.coeffs = malloc((new_degree + 1) * sizeof(int));
	
	return result;
}