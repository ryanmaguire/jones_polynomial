#include "double_polynomial.h"

/* Evaluates the double polynomial P at the given value x */
double evaluate_double_polynomial_double(const struct double_polynomial P, const double x) {
	double counter = 1; // We will multiply this by x over and over again to get x^exponent
	double result = 0;

	for (unsigned int exponent = 0; exponent <= P.degree; exponent++) {
		result += P.coeffs[exponent] * counter;

		counter *= x;
	}

	return result;
}