#include <stdio.h>
#include "double_polynomial.h"

void print_double_polynomial(const struct double_polynomial P, const char var)
{
	printf("%f%c^%d", P.coeffs[P.degree], var, P.degree);

	for (int i = P.degree - 1; i >= 0; i--) {
		if (P.coeffs[i] > 0) {
			printf(" +");
		} else if (P.coeffs[i] < 0) {
			printf(" ");
		}

		if (P.coeffs[i] != 0) {
			printf("%f%c^%d", P.coeffs[i], var, i);
		}
	}
}