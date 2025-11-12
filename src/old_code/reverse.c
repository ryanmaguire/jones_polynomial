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

void reverse(struct crossing* C) {
	struct crossing* temp_crossing;
	int temp_int;
	SWAP(temp_crossing, C->data[0], C->data[2]);
	SWAP(temp_crossing, C->data[1], C->data[3]);
	SWAP(temp_int, C->ports[0], C->ports[2]);
	SWAP(temp_int, C->ports[1], C->ports[3]);

	/*Make sure that ports connect correctly*/
	for (int i = 0; i < 4; i++)
		C->data[i]->ports[C->ports[i]] = i;

	/*flip direction*/
	C->direction = (C->direction + 2) % 4;
}
