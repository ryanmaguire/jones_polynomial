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

// Print the crossing connections of a link
void print_link(struct link* const L, enum boolean redo_ids)
{
    if (redo_ids == FALSE) {
        printf("First crossings in each component:\n");
        for (int component = 0; component < L->number_of_components; component++) {
            if (L->number_of_crossings_in_components[component] == 0) {
                continue;
            }
            printf("Component %d: %d\n", component, L->first_crossing_in_components[component]->id);
        }

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
                printf("Crossing %d: ", current_crossing->id);
                for (int i = 0; i < 4; i++) {
                    printf("%d -> %d (%d), ", i, current_crossing->data[i]->id, current_crossing->ports[i]);
                }
                printf("Components: O=%d, U=%d\n", current_crossing->over_component, current_crossing->under_component);

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
        return;
    }

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

    printf("First crossings in each component:\n");
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] == 0) {
            continue;
        }
        printf("Component %d: %d\n", component, L->first_crossing_in_components[component]->id);
    }

    /* Run through and print */
    current_id = 0;
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
            if (current_crossing->id >= current_id) {
                printf("Crossing %d: ", current_crossing->id);
                for (int i = 0; i < 4; i++) {
                    printf("%d -> %d (%d), ", i, current_crossing->data[i]->id, current_crossing->ports[i]);
                }
                printf("Components: O=%d, U=%d\n", current_crossing->over_component, current_crossing->under_component);
                current_id++;
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
}