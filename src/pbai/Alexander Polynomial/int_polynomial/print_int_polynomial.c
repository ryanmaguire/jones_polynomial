#include <stdio.h>
#include "int_polynomial.h"

/* Prints the polynomial P using the given char as its variable. Returns length of output. */
int print_int_polynomial(const struct int_polynomial P, const char var) 
{
	/* Keep track of length of output */
	int length = 0;

	length += printf("%d%c^%d", P.coeffs[P.degree], var, P.degree);

	for (int i = P.degree - 1; i >= 0; i--) {
		if (P.coeffs[i] > 0) {
			length += printf(" +");
		} else if (P.coeffs[i] < 0) {
			length += printf(" ");
		}

		if (P.coeffs[i] != 0) {
			length += printf("%d%c^%d", P.coeffs[i], var, i);
		}
	}

	return length;
}