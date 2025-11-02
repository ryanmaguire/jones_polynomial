#include "load_balanced.h"
struct bigon bfind(struct knot k){
    struct crossing *curr = k.first_crossing;
    int counter,counter1,counter2;
    for (counter = 0; counter < 2*k.number_of_crossings; counter++){
        for(counter1 = 0; counter1 < 4; counter1++){
            if (curr->data[counter1] == curr->data[(counter1+1)%4] && ((curr->ports[counter1] -  curr->ports[(counter1+1)%4])%4 == 1 ) && ((counter1 -  curr->ports[counter1])%2 == 1)){
                struct bigon b;
                b.C1 = curr;
                b.C2 = curr->data[counter1];
                b.port1 = curr->ports[counter1];
                b.port2 = curr->ports[(counter1+1)%4];
                return b;
            }
        }
        curr = next_crossing(curr,curr->direction);
    }
    // If none are found, return invalid bigon. Test for this in all functions using bfind.
    struct bigon b;
    b.C1 = NULL;
    b.C2 = NULL;
    b.port1 = -1;
    b.port2 = -1;
    return b;
}