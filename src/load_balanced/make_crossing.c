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

/* Function to make a crossing given its ID, data, port info, overdirection, and over & under components */
struct crossing* make_crossing(const int id, struct crossing** const data, const int* ports, const int overdirection, const int over_component, const int under_component) 
{
	struct crossing* temp = (struct crossing*)safe_malloc(sizeof(struct crossing));
	temp->id = id;
	for (int i = 0; i < 4; i++) {
		temp->data[i] = data[i];
		temp->ports[i] = ports[i];
	}
	temp->overdirection = overdirection;
	temp->over_component = over_component;
	temp->under_component = under_component;
	return temp;
}