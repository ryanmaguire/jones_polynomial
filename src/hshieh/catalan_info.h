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
#ifndef CATALAN_INFO_H
#define CATALAN_INFO_H

/*Array to store first 20 Catalan numbers*/
extern const int catalan[];

/*Array to store prefix of the sums involved in computing Catalan numbers
Catalan prefix[i][j] stores 0 if j = 0 or j > i, and otherwise, it equals
C_0C_{i - 1} + C_1C_{i - 2} + ... + C_{j - 1}C_{i - j} */
extern const int catalan_prefix[][20];

#endif
