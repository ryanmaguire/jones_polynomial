#include "int_polynomial.h"

/* Adds int polynomials a and b, returns the result */
struct int_polynomial add_int_polynomial(const struct int_polynomial P, const struct int_polynomial Q)
{
	struct int_polynomial result;

	if (P.degree < Q.degree) {
		result = new_int_polynomial(Q.degree);

		unsigned int i = 0;
		for (; i <= P.degree; i++) {
			result.coeffs[i] = P.coeffs[i] + Q.coeffs[i];
		}
		for (; i <= Q.degree; i++) {
			result.coeffs[i] = Q.coeffs[i];
		}
	}
	else {
		result = new_int_polynomial(P.degree);

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