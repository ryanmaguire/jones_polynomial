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

/*
Loop through every single link component and walk through the entire component
Begin by setting all status to -1
Then go back and loop again, numbering all the crossings from 0 to n-1 
Allocate memory for an array A of length n*sizeof(struct crossing)
The new crossing with number k will eventually have memory address A+k
*/

/* Function to make a deep copy of a link */
/* Renumbers ids in the original link L */
struct link* copy_link(const struct link* L)
{
    struct link* M = (struct link*) safe_malloc(sizeof(struct link));

    /* Set number_of_components */
    M->number_of_components = L->number_of_components;

    /* Set number_of_crossings_in_components */
    M->number_of_crossings_in_components = (int*) safe_malloc(MAX_CROSSINGS * sizeof(int));
    for (int i = 0; i < M->number_of_components; i++) {
        M->number_of_crossings_in_components[i] = L->number_of_crossings_in_components[i];
    }

    /* Allocate memory for first_crossing_in_components */
    M->first_crossing_in_components = (struct crossing**) safe_malloc(MAX_CROSSINGS * sizeof(struct crossing*));

    /* Reid every crossing from 0 to n-1
     * Allocate memory for all the new crossings
     * Old ids will now correspond to new memory addresses */

    /* Id every crossing to -1 */
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] == 0) {
            continue;
        }

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        int crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component]; 

        struct crossing* previous_crossing = NULL;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = (current_crossing->under_component == component) ? 2 : 1;
        do {
            current_crossing->id = -1;

            if (current_crossing->over_component == current_crossing->under_component) {
                crossings_left_to_visit -= 1;
            } else {
                crossings_left_to_visit -= 2;
            }

            previous_crossing = current_crossing;
            current_crossing = current_crossing->data[next_index];
            next_index = OPP(previous_crossing->ports[next_index]);
        } while (crossings_left_to_visit > 0);
    }

    /* Assign ids to every crossing from 0 to n-1, inclusive */
    int current_id = 0;
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] == 0) {
            continue;
        }

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        int crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component]; 

        struct crossing* previous_crossing = NULL;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = (current_crossing->under_component == component) ? 2 : 1;
        do {
            if (current_crossing->id == -1) {
                current_crossing->id = current_id++;
            }

            if (current_crossing->over_component == current_crossing->under_component) {
                crossings_left_to_visit -= 1;
            } else {
                crossings_left_to_visit -= 2;
            }

            previous_crossing = current_crossing;
            current_crossing = current_crossing->data[next_index];
            next_index = OPP(previous_crossing->ports[next_index]);
        } while (crossings_left_to_visit > 0);
    }

    /* We now know the total number of crossings */
    int number_of_crossings = current_id; // No OBOE becausee current_id was postcremented

    /* Allocate memory for new crossings */
    struct crossing** new_crossings_addresses = (struct crossing**) safe_malloc(number_of_crossings * sizeof(struct crossing*));
    for (int i = 0; i < number_of_crossings; i++) {
        new_crossings_addresses[i] = (struct crossing*) safe_malloc(sizeof(struct crossing));
    }

    /* Initialize all of the new crossings */
    /* We are guaranteed to go through L in the same order as we did when we first ided every crossing */
    int largest_seen_id = -1;
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] == 0) {
            continue;
        }

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        int crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component]; 

        struct crossing* previous_crossing = NULL;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = (current_crossing->under_component == component) ? 2 : 1;
        do {
            if (current_crossing->id > largest_seen_id) {
                /* Then, current_crossing->id must be largest_seen_id + 1 due to order preservation */
                largest_seen_id = current_crossing->id;

                /* Address of the new, copied crossing */
                struct crossing* copied_crossing = new_crossings_addresses[largest_seen_id];

                /* Copy data[4] over */
                for (int i = 0; i < 4; i++) {
                    copied_crossing->data[i] = new_crossings_addresses[current_crossing->data[i]->id];
                }

                /* Copy ports[4] over */
                for (int i = 0; i < 4; i++) {
                    copied_crossing->ports[i] = current_crossing->ports[i];
                }

                /* Copy everything else over */
                copied_crossing->overdirection = current_crossing->overdirection;
                copied_crossing->over_component = current_crossing->over_component;
                copied_crossing->under_component = current_crossing->under_component;
            }

            if (current_crossing->over_component == current_crossing->under_component) {
                crossings_left_to_visit -= 1;
            } else {
                crossings_left_to_visit -= 2;
            }

            previous_crossing = current_crossing;
            current_crossing = current_crossing->data[next_index];
            next_index = OPP(previous_crossing->ports[next_index]);
        } while (crossings_left_to_visit > 0);

        /* Now, current_crossing = L->first_crossing_in_components[component], so we can do this: */
        M->first_crossing_in_components[component] = new_crossings_addresses[L->first_crossing_in_components[component]->id];
    }

    SAFE_FREE(new_crossings_addresses);

    return M;
}
