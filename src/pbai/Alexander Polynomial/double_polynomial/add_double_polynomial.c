#include "double_polynomial.h"

/* Adds double polynomials a and b, returns the result */
struct double_polynomial add_double_polynomial(const struct double_polynomial P, const struct double_polynomial Q)
{
	struct double_polynomial result;

	if (P.degree < Q.degree) {
		result = new_double_polynomial(Q.degree);

		unsigned int i = 0;
		for (; i <= P.degree; i++) {
			result.coeffs[i] = P.coeffs[i] + Q.coeffs[i];
		}
		for (; i <= Q.degree; i++) {
			result.coeffs[i] = Q.coeffs[i];
		}
	}
	else {
		result = new_double_polynomial(P.degree);

		unsigned int i = 0;
		for (; i <= Q.degree; i++) {
			result.coeffs[i] = P.coeffs[i] + Q.coeffs[i];
		}
		for (; i <= P.degree; i++) {
			result.coeffs[i] = P.coeffs[i];
		}
	}

	return result;
}