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
#include "kauffman_implementation.h"
#include <ctype.h>

/*Function which converts from a letter-based DT notation to numerical labels. The labels use 0-indexing, so
A becomes 1, B becomes 3, C becomes 5, and so on for capital letters. For lowercase letters, the label is the
negative of the corresponding uppercase label. For invalid inputs, the function returns 0. */
int DT_letter_to_number(const char c) {
	if (islower(c))
		return 2 * ('a' - c) - 1;
	else if (isupper(c))
		return 2 * (c - 'A') + 1;

	return 0;
}
