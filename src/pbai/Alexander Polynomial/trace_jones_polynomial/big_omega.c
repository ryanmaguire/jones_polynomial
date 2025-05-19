#include "trace_jones_polynomial.h"

/* Calculates the sum z*Omega_1(t,k) + Omega_2(t,k) for an integer k not equal to 0 */
struct int_polynomial* big_omega(const int k)
{
	/* A solution to the recurrence relations given by the paper is as follows: */
	/* c_1(t,k) = 1 - t + t^2 - t^3 + . . . + (-1)^(k-1) * t^(k-1) */
	/* c_2(t,k) = 1 - c_1(t,k) = t - t^2 + t^3 + . . . + (-1)^k * t^(k-1) */
	/* c_3(t,k) = (-1)^(k-1) * c_1(t,k) */
	/* c_4(t,k) = (-1)^k * c_1(t,k+1) */
	
	/* The functions Omega_1(t,k) and Omega_2(t,k) are given by: */
	/* Omega_1(t,k) is equal to c_1(t,k) if k > 0 and is equal to t^k * c_3(t,-k) if k < 0 */
	/* Omega_2(t,k) is equal to c_2(t,k) if k > 0 and is equal to t^k * c_4(t,-k) if k < 0 */


}