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
#include <string.h>

/*Function which makes a DT knot given the DT code as a string*/
struct DT_knot make_DT_knot(char* DT_code) {
	/*Length of the string is the number of crossings, and the string is copied to the knot*/
	struct DT_knot temp;
	temp.number_of_crossings = (int)strlen(DT_code);
	temp.DT_code = (char*)safe_malloc((size_t)temp.number_of_crossings + 1);
	strcpy_s(temp.DT_code, (size_t)temp.number_of_crossings + 1, DT_code);
	return temp;
}
