/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of jones_polynomial.                                    *
 *                                                                            *
 *  jones_polynomial is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  jones_polynomial is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License along   *
 *  with jones_polynomial.  If not, see <https://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#include "skein_template.h"

struct laurent_polynomial Jones_Partial(struct Gauss k1) {
    // Jones specialization
    int z_coeffs[] = {-1, 0, 1};
    struct laurent_polynomial z = make_polynomial(-1, 1, z_coeffs);
    int delta_coeffs[] = { -1, 0, -1 };
    struct laurent_polynomial delta = make_polynomial(-1, 1, delta_coeffs);
    // Base case: no crossings
    if (k1.crossings == 0) {
        return polynomial_power(delta, k1.components - 1);
    }
    // Overcrossing: one branch (decorate)
    if (k1.ovorun == OVER) {
        struct Gauss k2 = virtue(k1);
        struct laurent_polynomial J2 = Jones_Partial(k2);
        free_gauss(k2);
        if (k1.sign == 1) {
            scale_polynomial(&J2, ALPHA_DEGREE);
            return J2;
        }
        if (k1.sign == -1) {
            scale_polynomial(&J2, -ALPHA_DEGREE);
            return J2;
        }
    }

    // Undercrossing: two branches (switch + splice)
    struct Gauss k2 = virtue(k1);
    struct laurent_polynomial J2 = Jones_Partial(k2);
    free_gauss(k2);

    struct Gauss k3 = splice(k1);
    struct laurent_polynomial J3 = Jones_Partial(k3);
    free_gauss(k3);

    if (k1.sign == 1) {
        scale_polynomial(&J2, -ALPHA_DEGREE);
        return add_polynomials(J2, multiply_polynomials(z, J3));
    }
    else {
        scale_polynomial(&J2, ALPHA_DEGREE);
        return subtract_polynomials(J2, multiply_polynomials(z, J3));
    }
}
