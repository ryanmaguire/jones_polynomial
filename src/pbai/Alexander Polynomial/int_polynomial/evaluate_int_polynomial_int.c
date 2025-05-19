#include "int_polynomial.h"

/* Evaluates the int polynomial P at the given value x */
int evaluate_int_polynomial_int(const struct int_polynomial P, const int x) {
	int counter = 1; // We will multiply this by x over and over again to get x^exponent
	int result = 0;

	for (unsigned int exponent = 0; exponent <= P.degree; exponent++) {
		result += P.coeffs[exponent] * counter;

		counter *= x;
	}

	return result;
}