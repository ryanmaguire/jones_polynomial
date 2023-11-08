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
#include "kauffman.h"

void simplify_chain(struct chain *c)
{
    struct chain *working, *tmp;
    unsigned int first, second, new_first, new_second;
    unsigned char pop = 0x00U;

    if (!c)
        return;

    working = c;

    /*  Rewind back to the start of the chain of ordered pairs.               */
    while (working->previous)
        working = working->previous;

    while (working)
    {
        first = working->current->dat[0];
        second = working->current->dat[1];

        new_first = first;
        new_second = second;

        /*  If this ordered pair is of the form (a, a) it is a cycle and we   *
         *  can move on to the next element.                                  */
        if (first == second)
        {
            working = working->next;
            continue;
        }

        tmp = working->next;

        while (tmp)
        {
            if (first == tmp->current->dat[0])
            {
                new_first = tmp->current->dat[1];
                pop = 0x01U;
            }

            else if (first == tmp->current->dat[1])
            {
                new_first = tmp->current->dat[0];
                pop = 0x01U;
            }

            else if (second == tmp->current->dat[0])
            {
                new_second = tmp->current->dat[1];
                pop = 0x01U;
            }

            else if (second == tmp->current->dat[1])
            {
                new_second = tmp->current->dat[0];
                pop = 0x01U;
            }

            if (pop)
            {
                pop_chain(tmp);
                tmp = working->next;
                first = new_first;
                second = new_second;
                pop = 0x00U;
            }

            else
                tmp = tmp->next;
        }

        working = working->next;
    }
}
