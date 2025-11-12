#ifndef INT_POLY_H
#define INT_POLY_H

#include <stdio.h>   
#include <stdlib.h> 

struct int_polynomial {
	unsigned int degree;
	int* coeffs;
};

/* Allocates memory for and returns an int polynomial struct given the degree */
extern struct int_polynomial new_int_polynomial(const int degree);

/* Adds int polynomials P and Q, returns the result */
extern struct int_polynomial add_int_polynomial(const struct int_polynomial P, const struct int_polynomial Q);

/* Multiplies int polynomials P and Q using naive O(nm) multiplication, returns the result */
extern struct int_polynomial multiply_int_polynomial(const struct int_polynomial P, const struct int_polynomial Q);

/* Prints the polynomial P using the given char as its variable. Returns length of output. */
extern int print_int_polynomial(const struct int_polynomial P, const char var);

/* Evaluates the int polynomial P at the given value x */
extern int evaluate_int_polynomial_int(const struct int_polynomial P, const int x);

#endif