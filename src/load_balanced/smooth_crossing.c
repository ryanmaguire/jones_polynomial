//SMOOTHINGS:
// 0 smoothing is K_0 if the thing is positive
// 1 smoothing is K_0 if the thing is negatived
// 0 smoothing function:
//    takes in a link and applies a 0 smoothing.
// Case 1: over_component = under_component -->
   // 2 cases: K_0 smoothing splits, other smoothing keeps it as one component
// Case 2: over component != undercomponent --> both smoothings merge
// 1 smoothing function:
//    takes in a link and applies a 1 smoothing.
// Case 1: over_component = under_component -->
   // 2 cases: K_0 smoothing splits, other smoothing keeps it as one component
// Case 2: over component != undercomponent --> both smoothings merge
// Now, iterate through each component and ensure that signs are good.
   // First, check the crossing after and move on --> Start loop + check whether curr = crossing after.
// Finally, if merge --> decrease # of components by 1, get rid of a crossing in the thing, and get rid of the component (shift).
// if split --> increase # by 1. Add component to the end of the list.
// if reconfig --> stay the same. Return neighbor for first_crossing of the component.
#include "load_balanced.h"

void smooth_crossing(struct link *K, struct crossing* C, int type)
{
   if (type == 0){// if 0 smoothing
       if (C->over_component == C->under_component){//If overstrand and understrand are the same
           if (C->overdirection == OVER_POS){// If positive (splits)
			  int overcomp = C->over_component;
              K->number_of_components++;//Increment number of components
			  C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
			  C->data[1]->data[C->ports[1]] = C->data[0];
			  C->data[2]->data[C->ports[2]] = C->data[3];
			  C->data[3]->data[C->ports[3]] = C->data[2];
			  C->data[0]->ports[C->ports[0]] = C->ports[1];
			  C->data[1]->ports[C->ports[1]] = C->ports[0];
			  C->data[2]->ports[C->ports[2]] = C->ports[3];
			  C->data[3]->ports[C->ports[3]] = C->ports[2];
			  struct crossing* current_crossing = C;
			  struct crossing* next_crossing = C->data[1];
			  int direction = OPP(C->ports[1]);
			  current_crossing = next_crossing;
			  if (direction % 2 == 0){
				current_crossing->under_component = K->number_of_components;
			  }
			  else{
				current_crossing->over_component = K->number_of_components;
			  }
			  while (current_crossing != C->data[1]){
				next_crossing = current_crossing->data[direction];
				int direction = OPP(current_crossing->ports[1]);
			  	current_crossing = next_crossing;
			  	if (direction % 2 == 0){
					current_crossing->under_component = K->number_of_components;
			  	}
			  	else{
					current_crossing->over_component = K->number_of_components;
			  	}
			  }
           }
           else{// If negative (number of comps stays the same)
			  C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
			  C->data[1]->data[C->ports[1]] = C->data[0];
			  C->data[2]->data[C->ports[2]] = C->data[3];
			  C->data[3]->data[C->ports[3]] = C->data[2];
			  C->data[0]->ports[C->ports[0]] = C->ports[1];
			  C->data[1]->ports[C->ports[1]] = C->ports[0];
			  C->data[2]->ports[C->ports[2]] = C->ports[3];
			  C->data[3]->ports[C->ports[3]] = C->ports[2];
			  struct crossing* current_crossing = C;
			  struct crossing* next_crossing = C->data[1];
			  int direction = OPP(C->ports[1]);
			  current_crossing = next_crossing;
			  while (current_crossing != C->data[1]){
				next_crossing = current_crossing->data[direction];
				int direction = OPP(current_crossing->ports[1]);
			  	current_crossing = next_crossing;
			  	if (direction = 0){
					
			  	}
			  	else{
					current_crossing->over_component = K->number_of_components;
			  	}
			  }
           }
       }
       else{
           if (C->overdirection == OVER_POS){// If positive (merge, but no sign check needed)
			  K->number_of_components -= 1;
			  C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
			  C->data[1]->data[C->ports[1]] = C->data[0];
			  C->data[2]->data[C->ports[2]] = C->data[3];
		      C->data[3]->data[C->ports[3]] = C->data[2];
			  C->data[0]->ports[C->ports[0]] = C->ports[1];
			  C->data[1]->ports[C->ports[1]] = C->ports[0];
			  C->data[2]->ports[C->ports[2]] = C->ports[3];
			  C->data[3]->ports[C->ports[3]] = C->ports[2];
           }
           else{// If negative (merge, but sign check needed)
              K->number_of_components -= 1;
			  C->data[0]->data[C->ports[0]] = C->data[1]; //Reattach Components
			  C->data[1]->data[C->ports[1]] = C->data[0];
			  C->data[2]->data[C->ports[2]] = C->data[3];
			  C->data[3]->data[C->ports[3]] = C->data[2];
			  C->data[0]->ports[C->ports[0]] = C->ports[1];
			  C->data[1]->ports[C->ports[1]] = C->ports[0];
			  C->data[2]->ports[C->ports[2]] = C->ports[3];
			  C->data[3]->ports[C->ports[3]] = C->ports[2];
           }
       }
   }
   if (type == 1){// if 1 smoothing
       if (C->over_component == C->under_component){//If overstrand and understrand are the same
           if (C->overdirection == OVER_POS){// If positive (number of components stays the same)
			  C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
			  C->data[3]->data[C->ports[3]] = C->data[0];
			  C->data[2]->data[C->ports[2]] = C->data[1];
			  C->data[1]->data[C->ports[1]] = C->data[2];
			  C->data[0]->ports[C->ports[0]] = C->ports[3];
			  C->data[3]->ports[C->ports[3]] = C->ports[0];
			  C->data[2]->ports[C->ports[2]] = C->ports[1];
			  C->data[1]->ports[C->ports[1]] = C->ports[2];
           }
           else{ // If negative, (splits)
              K->number_of_components++;
			  C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
			  C->data[3]->data[C->ports[3]] = C->data[0];
			  C->data[2]->data[C->ports[2]] = C->data[1];
			  C->data[1]->data[C->ports[1]] = C->data[2];
			  C->data[0]->ports[C->ports[0]] = C->ports[3];
			  C->data[3]->ports[C->ports[3]] = C->ports[0];
			  C->data[2]->ports[C->ports[2]] = C->ports[1];
			  C->data[1]->ports[C->ports[1]] = C->ports[2];
			  struct crossing* current_crossing = C;
			  struct crossing* next_crossing = C->data[1];
			  int direction = OPP(C->ports[1]);
			  current_crossing = next_crossing;
			  if (direction % 2 == 0){
				current_crossing->under_component = K->number_of_components;
			  }
			  else{
				current_crossing->over_component = K->number_of_components;
			  }
			  while (current_crossing != C->data[1]){
				next_crossing = current_crossing->data[direction];
				int direction = OPP(current_crossing->ports[1]);
			  	current_crossing = next_crossing;
			  	if (direction % 2 == 0){
					current_crossing->under_component = K->number_of_components;
			  	}
			  	else{
					current_crossing->over_component = K->number_of_components;
			  	}
			  }
           }
       }
       else{
           if (C->overdirection == OVER_POS){// If positive (merge, but sign check needed)
				K->number_of_components -= 1;
				C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
			  	C->data[3]->data[C->ports[3]] = C->data[0];
			  	C->data[2]->data[C->ports[2]] = C->data[1];
			  	C->data[1]->data[C->ports[1]] = C->data[2];
				C->data[0]->ports[C->ports[0]] = C->ports[3];
			    C->data[3]->ports[C->ports[3]] = C->ports[0];
			    C->data[2]->ports[C->ports[2]] = C->ports[1];
			    C->data[1]->ports[C->ports[1]] = C->ports[2];
           }
           else{//If negative (merge, but no sign check needed)
				K->number_of_components -= 1;
				C->data[0]->data[C->ports[0]] = C->data[3]; //Reattach Components
			  	C->data[3]->data[C->ports[3]] = C->data[0];
			  	C->data[2]->data[C->ports[2]] = C->data[1];
			  	C->data[1]->data[C->ports[1]] = C->data[2];
				C->data[0]->ports[C->ports[0]] = C->ports[3];
			    C->data[3]->ports[C->ports[3]] = C->ports[0];
			    C->data[2]->ports[C->ports[2]] = C->ports[1];
			    C->data[1]->ports[C->ports[1]] = C->ports[2];
           }
       }
   }
}

