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
#ifndef KNOT_DATA_H
#define KNOT_DATA_H

/*  The Figure-Eight knot.                                                    */
#define FIGURE_EIGHT "O0- U1+ O2+ U0- O3- U2+ O1+ U3-"

/*  Both the right-handed and left-handed trefoils.                           */
#define RIGHT_HANDED_TREFOIL "O0+ U1+ O2+ U0+ O1+ U2+"
#define LEFT_HANDED_TREFOIL "O0- U1- O2- U0- O1- U2-"

/*  The right and left-handed chain-link fence knots (virtual knots, genus 1.)*/
#define RIGHT_HANDED_CHAIN_LINK_FENCE "O0+ O1+ U0+ U1+"
#define LEFT_HANDED_CHAIN_LINK_FENCE "O0- O1- U0- U1-"

/*  T(25, 2) torus knot. Large knot, 25 crossings, takes a few seconds. The   *
 *  previous knots can have their Jones polynomials computed almost instantly *
 *  (the computation takes a few milliseconds).                               */
#define T25_2_TORUS_KNOT "U0+ O1+ U2+ O3+ U4+ O5+ U6+ O7+ U8+ O9+ U10+ " \
                         "O11+ U12+ O13+ U14+ O15+ U16+ O17+ U18+ O19+ " \
                         "U20+ O21+ U22+ O23+ U24+ O0+ U1+ O2+ U3+ O4+ " \
                         "U5+ O6+ U7+ O8+ U9+ O10+ U11+ O12+ U13+ O14+ " \
                         "U15+ O16+ U17+ O18+ U19+ O20+ U21+ O22+ U23+ O24+"

#endif
