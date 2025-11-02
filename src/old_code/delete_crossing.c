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

void delete_crossing(struct crossing* C, int direction) {
	struct crossing* next = C->data[direction];
	int next_port = C->ports[direction];
	struct crossing* previous = C->data[(direction + 2) % 4];
	int previous_port = C->ports[(direction + 2) % 4];
	next->data[next_port] = previous;
	next->ports[next_port] = previous_port;
	previous->data[previous_port] = next;
	previous->ports[previous_port] = next_port;
}
