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


void smooth_crossing(struct link *L, struct crossing* C, int type)//Type 0 means 0-smoothing, type 1 means 1-smoothing
{
    int crossing_0_pair, crossing_2_pair; //Variables to hold which crossings to pair
    if (type == 0) {//If 0-smoothing
        crossing_0_pair = 1;//Pair crossing 0 with crossing 1
        crossing_2_pair = 3;//Pair crossing 2 with crossing 3
    } else {// If 1-smoothing
        crossing_0_pair = 3;// Pair crossing 0 with crossing 3
        crossing_2_pair = 1;// Pair crossing 2 with crossing 1
    }
    pair_crossings(C->data[0], C->ports[0], C->data[crossing_0_pair], C->ports[crossing_0_pair]);//Pair the crossings
    pair_crossings(C->data[2], C->ports[2], C->data[crossing_2_pair], C->ports[crossing_2_pair]);//Pair the crossings
    if (C->over_component == C->under_component) {//If overstrand and understrand are the same
        if ((C->overdirection == OVER_POS && type == 0) || (C->overdirection == OVER_NEG && type == 1)) {// If positive (splits)
            L->number_of_components++;//Increment number of components
            /* Reattach components */
           
            struct crossing* current_crossing = C; // current_crossing is a pointer to a crossing
            struct crossing* next_crossing = C->data[1];//next_crossing is a pointer to a different crossing.
            int direction = OPP(C->ports[1]);//Get the opposite port direction
            current_crossing = next_crossing;//Set current crossing to next crossing
            if (direction % 2 == 0) {//If even (understrand)
                current_crossing->under_component = L->number_of_components-1;//Set under_component to new component number
            }
            else {//If odd (overstrand)
                current_crossing->over_component = L->number_of_components-1;
            }
            do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (direction % 2 == 0) {
                    current_crossing->under_component = L->number_of_components-1;
                }
                else {
                    current_crossing->over_component = L->number_of_components-1;
                }
            } while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));
            L->first_crossing_in_components[L->number_of_components-1]=C->data[1];
            L->first_crossing_in_components[C->over_component]=C->data[3];
            int counter1 = 0;
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
            int counter2 = 0;
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
            L->number_of_crossings_in_components[L->number_of_components-1] = counter1 / 2;
            delete_crossing(&C);
        }
        else {// If negative (number of comps stays the same)
            struct crossing* current_crossing = C;
            struct crossing* next_crossing = C->data[1];
            int direction = OPP(C->ports[1]);
            current_crossing = next_crossing;
            do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (direction == 0) {
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                    SWAP(struct crossing*, current_crossing->data[0], current_crossing->data[2]);
                    SWAP(struct crossing*, current_crossing->data[1], current_crossing->data[3]);
                    SWAP(int, current_crossing->ports[0], current_crossing->ports[2]);
                    SWAP(int, current_crossing->ports[1], current_crossing->ports[3]);
                    for (int i = 0; i < 4; i++) {
                        if (current_crossing->data[i] != current_crossing) {
                            current_crossing->data[i]->ports[current_crossing->ports[i]] = i;
                        } else {
                            current_crossing->ports[i] = OPP(current_crossing->ports[i]);
                        }
                    }
                    direction = 2;
                }
                else if ((direction % 2 == 1) && (direction != current_crossing->overdirection)){
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                }
            } while (!(current_crossing == C->data[1] && direction % 2 == OPP(C->ports[1]) % 2));
            L->number_of_crossings_in_components[C->over_component] -=1;
            if (L->first_crossing_in_components[C->over_component] == C){
                L->first_crossing_in_components[C->over_component] = C->data[1];
            }
            delete_crossing(&C);
        }
    } else {
        if ((C->overdirection == OVER_POS && type == 0) || (C->overdirection == OVER_NEG && type == 1)){//If K0 (merge & slide down)
            struct crossing* current_crossing = C;//current crossing is C
            struct crossing* next_crossing = C->data[1];//next crossing is C->data[1]
            int comp_1 = C->over_component;//comp_1 is overcomponent
            int comp_2 = C->under_component;//comp_2 is undercomponent
            int newcomp = (comp_1>comp_2)? comp_2:comp_1;//newcomp is smaller
            int oldcomp = (comp_1>comp_2)? comp_1:comp_2;//oldcomp is greater
            int overlap = 0;//number of crossings in both oldcomp and newcomp
            int direction = OPP(C->ports[1]);//direction I go should exit C->ports[1] to go straight after I go out from C toward C->ports[1]
            current_crossing = next_crossing;//current crossing should be C->data[1]
            if (current_crossing->under_component == oldcomp && newcomp == current_crossing->over_component
                || current_crossing->over_component == oldcomp && newcomp == current_crossing->under_component){
                overlap++;
            }
            do {//Update components. If I have something that was in oldcomp, it should now be in newcomp.
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (current_crossing->under_component == oldcomp && newcomp == current_crossing->over_component
                    || current_crossing->over_component == oldcomp && newcomp == current_crossing->under_component){
                    overlap++;
                }
                if (current_crossing->over_component == oldcomp){//If I'm going over
                    current_crossing->over_component = newcomp;//do the overcomponent
                }
                if (current_crossing->under_component == oldcomp){//if I'm going under
                    current_crossing->under_component = newcomp;//do the undercomponent
                }
            } while (!(current_crossing == C->data[1] && direction == OPP(C->ports[1])));

            int counter;//define counter
            for (counter = 1; counter< L->number_of_components - oldcomp; counter++){//Shift everything to the left; loop over everything above oldcomp
                if (L->number_of_crossings_in_components[oldcomp+counter] == 0) {
                    continue;
                }
                current_crossing = L->first_crossing_in_components[oldcomp+counter];
                int d =  (current_crossing->under_component == oldcomp+counter) ? 2 : 1;
                next_crossing = current_crossing->data[d];
                if (current_crossing->over_component == oldcomp+counter){
                    current_crossing->over_component = oldcomp+counter-1;
                }
                if (current_crossing->under_component == oldcomp+counter){
                    current_crossing->under_component = oldcomp+counter-1;
                }
                direction = OPP(current_crossing->ports[d]);
                current_crossing = next_crossing;
                do {
                    next_crossing = current_crossing->data[direction];
                    direction = OPP(current_crossing->ports[direction]);
                    current_crossing = next_crossing;
                    if (current_crossing->over_component == oldcomp+counter){
                        current_crossing->over_component = oldcomp+counter-1;
                    }
                    if (current_crossing->under_component == oldcomp+counter){
                        current_crossing->under_component = oldcomp+counter-1;
                    }
                } while (!(current_crossing == L->first_crossing_in_components[oldcomp+counter]->data[d] && direction == OPP(L->first_crossing_in_components[oldcomp+counter]->ports[d])));
                
                L->first_crossing_in_components[oldcomp+counter-1] = L->first_crossing_in_components[oldcomp+counter];
            }
            if (L->first_crossing_in_components[newcomp] == C){
                L->first_crossing_in_components[newcomp] = C->data[1];
            }
            int number = L->number_of_crossings_in_components[oldcomp]+L->number_of_crossings_in_components[newcomp]-overlap-1; //Working here
            L->number_of_crossings_in_components[newcomp] = number;
            for (counter = 1; counter< L->number_of_components - oldcomp; counter++){//Shift everything to the left; loop over everything above oldcomp
                L->number_of_crossings_in_components[oldcomp+counter-1] = L->number_of_crossings_in_components[oldcomp+counter];
            }
            L->number_of_components -= 1;
            delete_crossing(&C);
        }
        else {// If negative (merge, but sign check needed)
            struct crossing* current_crossing = C;
            struct crossing* next_crossing = C->data[1];
            int comp_1 = C->over_component;
            int comp_2 = C->under_component;
            int newcomp = (comp_1>comp_2)? comp_2:comp_1;
            int oldcomp = (comp_1>comp_2)? comp_1:comp_2;
            int direction = OPP(C->ports[1]);
            int overlap = 0;
            current_crossing = next_crossing;
            if (current_crossing->under_component == oldcomp && newcomp == current_crossing->over_component
                || current_crossing->over_component == oldcomp && newcomp == current_crossing->under_component){
                overlap++;
            }
            do {
                next_crossing = current_crossing->data[direction];
                direction = OPP(current_crossing->ports[direction]);
                current_crossing = next_crossing;
                if (current_crossing->under_component == oldcomp && newcomp == current_crossing->over_component
                    || current_crossing->over_component == oldcomp && newcomp == current_crossing->under_component){
                    overlap++;
                }
                if (current_crossing->over_component == oldcomp){
                    current_crossing->over_component = newcomp;
                }
                if (current_crossing->under_component == oldcomp){
                    current_crossing->under_component = newcomp;
                }
                if (direction == 0){
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                    SWAP(struct crossing*, current_crossing->data[0], current_crossing->data[2]);
                    SWAP(struct crossing*, current_crossing->data[1], current_crossing->data[3]);
                    SWAP(int, current_crossing->ports[0], current_crossing->ports[2]);
                    SWAP(int, current_crossing->ports[1], current_crossing->ports[3]);
                    for (int i = 0; i < 4; i++) {
                        if (current_crossing->data[i] != current_crossing) {
                            current_crossing->data[i]->ports[current_crossing->ports[i]] = i;
                        } else {
                            current_crossing->ports[i] = OPP(current_crossing->ports[i]);
                        }
                    }
                    direction = 2;
                } else if ((direction % 2 == 1) && (direction != current_crossing->overdirection)){
                    current_crossing->overdirection = OPP(current_crossing->overdirection);//Switch sign of crossing as I swap the strand
                }
            } while (!(current_crossing == C->data[1] && direction % 2 == OPP(C->ports[1]) % 2));

            int counter;
            for (counter = 1; counter< L->number_of_components - oldcomp; counter++){
                if (L->number_of_crossings_in_components[oldcomp+counter] == 0) {
                    continue;
                }
                current_crossing = L->first_crossing_in_components[oldcomp+counter];
                int d =  (current_crossing->under_component == oldcomp+counter) ? 2 : 1;
                next_crossing = current_crossing->data[d];
                do {
                    if (current_crossing->over_component == oldcomp+counter){
                        current_crossing->over_component = oldcomp+counter-1;
                    }
                    if (current_crossing->under_component == oldcomp+counter){
                        current_crossing->under_component = oldcomp+counter-1;
                    }
                    direction = OPP(current_crossing->ports[direction]);
                    current_crossing = next_crossing;
                } while (!(current_crossing == L->first_crossing_in_components[oldcomp+counter]->data[d] && direction == OPP(L->first_crossing_in_components[oldcomp+counter]->ports[d])));
                L->first_crossing_in_components[oldcomp+counter-1] = L->first_crossing_in_components[oldcomp+counter];
            }
            if (L->first_crossing_in_components[newcomp] == C){
                L->first_crossing_in_components[newcomp] = C->data[1];
            }
            int number = L->number_of_crossings_in_components[oldcomp]+L->number_of_crossings_in_components[newcomp]-overlap-1; 
            L->number_of_crossings_in_components[newcomp] = number;
            for (counter = 1; counter< L->number_of_components - oldcomp; counter++){//Shift everything to the left; loop over everything above oldcomp
                L->number_of_crossings_in_components[oldcomp+counter-1] = L->number_of_crossings_in_components[oldcomp+counter];
            }
            L->number_of_components -= 1;
            delete_crossing(&C);
        }
    }
}



