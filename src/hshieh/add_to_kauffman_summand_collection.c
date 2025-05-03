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

/*Function which adds a kaufman summand to a collection/array of kauffman summands */
void add_to_kauffman_summand_collection(struct kauffman_summand** summand_collection, struct kauffman_summand* P) {
	/*First, find the index of the basis tangle from the kauffman summand*/
	int index = tangle_index(&P->basis_tangle);
	if (summand_collection[index] == NULL) 
		/*If the current entry at the index is null, then nothing has been added yet, so set it equal to P*/
		summand_collection[index] = P;
	else 
		/*Otherwise, add P to the current kauffman summand at the index*/
		add_to_kauffman_summand(summand_collection[index], P);
}
