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
#include <ctype.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_string.h>
#include "kauffman.h"

struct knot knot_from_gauss_code(const char *code)
{
    enum crossing_sign sign_buffer[2U * MAX_CROSSINGS];
    enum crossing_type type_buffer[2U * MAX_CROSSINGS];
    unsigned int crossing_buffer[2U * MAX_CROSSINGS];
    unsigned int index = 0U;
    unsigned int n;
    struct knot out;
    const char *tmp;
    char *whole_string = tmpl_String_Duplicate(code);
    char *str = whole_string;

    tmpl_String_Remove_Whitespace(str);
    tmpl_String_Make_Lower_Case(str);

    while (*str)
    {
        if (*str == 'o')
            type_buffer[index] = over_crossing;
        else
            type_buffer[index] = under_crossing;

        str++;
        tmp = str;

        while (isdigit(*str))
            str++;

        crossing_buffer[index] = strtol(tmp, NULL, 10);

        if (*str == '+')
            sign_buffer[index] = positive_crossing;
        else
            sign_buffer[index] = negative_crossing;

        index++;
        str++;
    }

    out.number_of_crossings = index >> 1U;
    out.crossing_number = malloc(sizeof(*out.crossing_number) * index);
    out.type = malloc(sizeof(*out.type) * index);
    out.sign = malloc(sizeof(*out.sign) * index);

    for (n = 0U; n < index; ++n)
    {
        out.crossing_number[n] = crossing_buffer[n];
        out.type[n] = type_buffer[n];
        out.sign[n] = sign_buffer[n];
    }

    free(whole_string);
    return out;
}
