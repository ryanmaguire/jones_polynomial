//SMOOTHINGS:
// 0 smoothing is L_0 if the thing is positive
// 1 smoothing is L_0 if the thing is negative
// 0 smoothing function:
//    takes in a link and applies a 0 smoothing.
// Case 1: over_component = under_component -->
   // 2 cases: L_0 smoothing splits, other smoothing keeps it as one component
// Case 2: over component != undercomponent --> both smoothings merge
// 1 smoothing function:
//    takes in a link and applies a 1 smoothing.
// Case 1: over_component = under_component -->
   // 2 cases: L_0 smoothing splits, other smoothing keeps it as one component
// Case 2: over component != undercomponent --> both smoothings merge
// Now, iterate through each component and ensure that signs are good.
   // First, check the crossing after and move on --> Start loop + check whether curr = crossing after.
// Finally, if merge --> decrease # of components by 1, get rid of a crossing in the thing, and get rid of the component (shift).
// if split --> increase # by 1. Add component to the end of the list.
// if reconfig --> stay the same. Return neighbor for first_crossing of the component.

//For number of crossings in components, 
#include "load_balanced.h"

void smooth_crossing(struct link *L, struct crossing* C, int type){
    if (C->over_component == C->under_component) {//If overstrand and understrand are the same
        if ((C->overdirection == OVER_POS & type == 0) || (C->overdirection == OVER_NEG & type == 1)) {// If positive (splits)
            int overcomp = C->over_component;
            L->number_of_components++;//Increment number of components
            if (type == 0){
                C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
                C->data[1]->data[C->ports[1]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[3];
                C->data[3]->data[C->ports[3]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[1];//Ensure that ports are named correctly
                C->data[1]->ports[C->ports[1]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[3];
                C->data[3]->ports[C->ports[3]] = C->ports[2];
            }
            else{
                C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
                C->data[3]->data[C->ports[3]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[1];
                C->data[1]->data[C->ports[1]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[3];//Ensure that ports are named correctly
                C->data[3]->ports[C->ports[3]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[1];
                C->data[1]->ports[C->ports[1]] = C->ports[2];
            }
            struct crossing* current_crossing = C; // current_crossing is a pointer to a crossing
            struct crossing* next_crossing = C->data[1];//next_crossing is a pointer to a different crossing.
            int direction = OPP(C->ports[1]);
            current_crossing = next_crossing;
            if (direction % 2 == 0) {
                current_crossing->under_component = L->number_of_components;
            }
            else {
                current_crossing->over_component = L->number_of_components;
            }
            do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (direction % 2 == 0) {
                    current_crossing->under_component = L->number_of_components;
                }
                else {
                    current_crossing->over_component = L->number_of_components;
                }
            } while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));
			L->first_crossing_in_components[L->number_of_components]=C->data[1];
			current_crossing = C;
            next_crossing = C->data[3];
            direction = OPP(C->ports[3]);
            current_crossing = next_crossing;
		    do{
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
            } while (!(current_crossing == C->data[3] && direction == OPP(C->ports[3])));
			L->first_crossing_in_components[C->over_component]=C->data[3];
			int counter1;
			current_crossing = C;
            next_crossing = C->data[1];
            direction = OPP(C->ports[1]);
            current_crossing = next_crossing;
		    do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
				if (current_crossing->over_component == current_crossing->under_component){
					counter1++;
				}
				else{
					counter1 += 2;
				}
            } while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));
			int counter2;
			current_crossing = C;
            next_crossing = C->data[3];
            direction = OPP(C->ports[3]);
            current_crossing = next_crossing;
		    do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
				if (current_crossing->over_component == current_crossing->under_component) {
					counter2++;
				}
				else {
					counter2 += 2;
				}
            } while (!(current_crossing == C->data[3] && direction == OPP(C->ports[3])));
			L->number_of_crossings_in_components[C->over_component] = counter2 / 2; // These counters are guaranteed to be even
			L->number_of_crossings_in_components[L->number_of_components] = counter1 / 2;
			delete_crossing(C);
        } else {// If negative (number of comps stays the same)
            if (type == 0){
                C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
                C->data[1]->data[C->ports[1]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[3];
                C->data[3]->data[C->ports[3]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[1];//Ensure that ports are named correctly
                C->data[1]->ports[C->ports[1]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[3];
                C->data[3]->ports[C->ports[3]] = C->ports[2];
            }
            else{
                C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
                C->data[3]->data[C->ports[3]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[1];
                C->data[1]->data[C->ports[1]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[3];//Ensure that ports are named correctly
                C->data[3]->ports[C->ports[3]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[1];
                C->data[1]->ports[C->ports[1]] = C->ports[2];
            }
            struct crossing* current_crossing = C;
            struct crossing* next_crossing = C->data[1];
            struct crossing* temp_crossing;
            int temp_int;
            int direction = OPP(C->ports[1]);
            current_crossing = next_crossing;
			do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (direction == 0) {
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                    SWAP(temp_crossing, current_crossing->data[0], current_crossing->data[2]);
                    SWAP(temp_int, current_crossing->ports[0], current_crossing->ports[2]);
                    current_crossing->data[0]->ports[current_crossing->ports[0]] = 0;
                    current_crossing->data[2]->ports[current_crossing->ports[2]] = 2;
					direction = 2;
                }
                else if ((direction % 2 == 1) && (direction != current_crossing->overdirection)){
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                }
    		} while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));
			L->number_of_crossings_in_components[C->over_component] -=1;
            if (L->first_crossing_in_components[C->over_component] == C){
                L->first_crossing_in_components[C->over_component] = C->data[1];
            }
			delete_crossing(C);
        }
	} else {
        if ((C->overdirection == OVER_POS & type == 0) || (C->overdirection == OVER_NEG & type == 1)){// If positive (merge, but no sign check needed)
            L->number_of_components -= 1;
            if (type == 0){
                C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
                C->data[1]->data[C->ports[1]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[3];
                C->data[3]->data[C->ports[3]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[1];//Ensure that ports are named correctly
                C->data[1]->ports[C->ports[1]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[3];
                C->data[3]->ports[C->ports[3]] = C->ports[2];
            }
            else{
                C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
                C->data[3]->data[C->ports[3]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[1];
                C->data[1]->data[C->ports[1]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[3];//Ensure that ports are named correctly
                C->data[3]->ports[C->ports[3]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[1];
                C->data[1]->ports[C->ports[1]] = C->ports[2];
            }
            struct crossing* current_crossing = C;
            struct crossing* next_crossing = C->data[1];
            int comp_1 = C->over_component;
            int comp_2 = C->under_component;
            int newcomp = (comp_1>comp_2)? comp_2:comp_1;
            int oldcomp = (comp_1>comp_2)? comp_1:comp_2;
            int direction = OPP(C->ports[1]);
            current_crossing = next_crossing;
            do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (current_crossing->over_component == oldcomp){
                    current_crossing->over_component = newcomp;
                }
                if (current_crossing->under_component == oldcomp){
                    current_crossing->under_component = newcomp;
                }
            } while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));
            int counter;
            for (counter = 0; counter< L->number_of_components - oldcomp+1; counter++){
                current_crossing = L->first_crossing_in_components[oldcomp+counter+1];
                if (current_crossing->over_component == oldcomp+counter+1){
                    current_crossing->over_component = oldcomp+counter;
                }
                if (current_crossing->under_component == oldcomp+counter+1){
                    current_crossing->under_component = oldcomp+counter;
                }
				direction = 1;
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                do {
                    next_crossing = current_crossing->data[direction];
                    direction = OPP(current_crossing->ports[direction]);
                    current_crossing = next_crossing;
                    if (current_crossing->over_component == oldcomp+counter+1){
                        current_crossing->over_component = oldcomp+counter;
                    }
                    if (current_crossing->under_component == oldcomp+counter+1){
                        current_crossing->under_component = oldcomp+counter;
                    }
                } while (!(current_crossing == L->first_crossing_in_components[oldcomp+counter+1] && direction == OPP(L->first_crossing_in_components[oldcomp+counter+1]->ports[1])));
                L->first_crossing_in_components[oldcomp+counter] = L->first_crossing_in_components[oldcomp+counter+1];
            }
            if (L->first_crossing_in_components[newcomp] == C){
                L->first_crossing_in_components[newcomp] = C->data[1];
            }
			int number = L->number_of_crossings_in_components[oldcomp]+L->number_of_crossings_in_components[newcomp]-1; //Working here
            L->number_of_crossings_in_components[newcomp] = number;
			delete_crossing(C);
	    }
        else {// If negative (merge, but sign check needed)
            L->number_of_components -= 1;
            if (type == 0){
                C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
                C->data[1]->data[C->ports[1]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[3];
                C->data[3]->data[C->ports[3]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[1];//Ensure that ports are named correctly
                C->data[1]->ports[C->ports[1]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[3];
                C->data[3]->ports[C->ports[3]] = C->ports[2];
            }
            else{
                C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
                C->data[3]->data[C->ports[3]] = C->data[0];
                C->data[2]->data[C->ports[2]] = C->data[1];
                C->data[1]->data[C->ports[1]] = C->data[2];
                C->data[0]->ports[C->ports[0]] = C->ports[3];//Ensure that ports are named correctly
                C->data[3]->ports[C->ports[3]] = C->ports[0];
                C->data[2]->ports[C->ports[2]] = C->ports[1];
                C->data[1]->ports[C->ports[1]] = C->ports[2];
            }
			struct crossing* current_crossing = C;
            struct crossing* next_crossing = C->data[1];
			struct crossing* temp_crossing;
            int temp_int;
            int comp_1 = C->over_component;
            int comp_2 = C->under_component;
            int newcomp = (comp_1>comp_2)? comp_2:comp_1;
            int oldcomp = (comp_1>comp_2)? comp_1:comp_2;
            int direction = OPP(C->ports[1]);
            current_crossing = next_crossing;
            do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (current_crossing->over_component == oldcomp){
                    current_crossing->over_component = newcomp;
                }
                if (current_crossing->under_component == oldcomp){
                    current_crossing->under_component = newcomp;
                }
            } while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));
            int counter;
            for (counter = 0; counter< L->number_of_components - oldcomp+1; counter++){
                current_crossing = L->first_crossing_in_components[oldcomp+counter+1];
                if (current_crossing->over_component == oldcomp+counter+1){
                    current_crossing->over_component = oldcomp+counter;
                }
                if (current_crossing->under_component == oldcomp+counter+1){
                    current_crossing->under_component = oldcomp+counter;
                }
				if (direction == 0){
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                    SWAP(temp_crossing, current_crossing->data[0], current_crossing->data[2]);
                    SWAP(temp_int, C->ports[0], C->ports[2]);
                    current_crossing->data[0]->ports[current_crossing->ports[0]] = 0;
                    current_crossing->data[2]->ports[current_crossing->ports[2]] = 2;
					direction = 2;
                } else if ((direction % 2 == 1) && (direction != current_crossing->overdirection)){
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                }
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                do {
                    next_crossing = current_crossing->data[direction];
                    direction = OPP(current_crossing->ports[direction]);
                    current_crossing = next_crossing;
                    if (current_crossing->over_component == oldcomp+counter+1){
                        current_crossing->over_component = oldcomp+counter;
                    }
                    if (current_crossing->under_component == oldcomp+counter+1){
                        current_crossing->under_component = oldcomp+counter;
                    }
                } while (!(current_crossing == L->first_crossing_in_components[oldcomp+counter+1] && direction == OPP(L->first_crossing_in_components[oldcomp+counter+1]->ports[1])));
                L->first_crossing_in_components[oldcomp+counter] = L->first_crossing_in_components[oldcomp+counter+1];
            }
            if (L->first_crossing_in_components[newcomp] == C){
                L->first_crossing_in_components[newcomp] = C->data[1];
            }
            int number = L->number_of_crossings_in_components[oldcomp]+L->number_of_crossings_in_components[newcomp]-1; //Working here
            L->number_of_crossings_in_components[newcomp] = number;
			delete_crossing(C);
        }
    }
}
