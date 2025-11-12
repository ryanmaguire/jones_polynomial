#ifndef DOUBLE_POLY_H
#define DOUBLE_POLY_H

#include <stdio.h>   
#include <stdlib.h> 

struct double_polynomial {
	unsigned int degree;
	double* coeffs;
};

/* Allocates memory for and returns an double polynomial struct given the degree */
extern struct double_polynomial new_double_polynomial(const int degree);

/* Adds double polynomials P and Q, returns the result */
extern struct double_polynomial add_double_polynomial(const struct double_polynomial P, const struct double_polynomial Q);

/* Multiplies double polynomials P and Q using naive O(nm) multiplication, returns the result */
extern struct double_polynomial multiply_double_polynomial(const struct double_polynomial P, const struct double_polynomial Q);

/* Multiplies double polynomial P by a scalar lambda */
extern struct double_polynomial scale_double_polynomial(const struct double_polynomial P, const double lambda);

/* Prints the polynomial P using the given char as its variable */
extern void print_double_polynomial(const struct double_polynomial P, const char var);

/* Evaluates the double polynomial P at the given value x */
extern double evaluate_double_polynomial_double(const struct double_polynomial P, const double x);

#endif