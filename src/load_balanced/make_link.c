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
 *
 *  with jones_polynomial.  If not, see <https://www.gnu.org/licenses/>.      *
 ******************************************************************************/
#include "load_balanced.h"

/* Function to make a link given its number of components, number of crossings in each component, and first crossing in each component */
struct link*
make_link(const size_t number_of_components,
          size_t * const number_of_crossings_in_components,
		  struct crossing** const first_crossing_in_components)
{
	struct link* temp = (struct link*)safe_malloc(sizeof(struct link));
	temp->number_of_components = number_of_components;
	temp->number_of_crossings_in_components = number_of_crossings_in_components;
	temp->first_crossing_in_components = first_crossing_in_components;
	return temp;
}