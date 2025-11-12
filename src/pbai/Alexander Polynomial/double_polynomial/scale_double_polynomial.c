#include "double_polynomial.h"

/* Multiplies double polynomial P by a scalar lambda */
extern struct double_polynomial scale_double_polynomial(const struct double_polynomial P, const double lambda)
{
	struct double_polynomial result = new_double_polynomial(P.degree);

	// Initialize everything in result to 0
	for (unsigned int i = 0; i <= result.degree; i++) {
		result.coeffs[i] = 0;
	}

	for (unsigned int index = 0; index <= P.degree; index++) {
		result.coeffs[index] = lambda * P.coeffs[index];
	}

	return result;
}
