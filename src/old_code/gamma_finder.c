#include "load_balanced.h"
struct gamma gfind(struct knot k){
    struct crossing *curr = k.first_crossing;
    int counter,counter1,counter2;
    for (counter = 0; counter < 2*k.number_of_crossings; counter++){
        for(counter1 = 0; counter1 < 4; counter1++){
            if (curr->data[counter1] == curr->data[(counter1+1)%4] && ((curr->ports[counter1] -  curr->ports[(counter1+1)%4]+4)%4 == 1 ) && ((counter1 - curr->ports[counter1]+2)%2 == 1)){
               if(curr->data[counter1]->data[(curr->ports[counter1]+2)%4] == curr->data[(counter1+1)%4]||curr->data[counter1]->data[(curr->ports[counter1]+2)%4] == curr->data[(counter1+3)%4]){
                     struct gamma g;
                     g.B.C1 = curr;
                     g.B.C2 = curr->data[counter1];
                     g.B.port1 = curr->ports[counter1];
                     g.B.port2 = curr->ports[(counter1+1)%4];
                     g.C3 = curr->data[counter1]->data[(curr->ports[counter1]+2)%4];
                     g.port3 = curr->data[counter1]->ports[(curr->ports[(counter1+2)%4]+2)%4];
                     if(curr->data[counter1]->data[(curr->ports[counter1]+2)%4] == curr->data[(counter1+1)%4]){
                          g.port4 = (counter1+1)%4;
                     }else{
                          g.port4 = (counter1+3)%4;
                     }
                     return g;
               }
            }
        }
        curr = next_crossing(curr,curr->direction);
    }
    // If none are found, return invalid bigon. Test for this in all functions using bfind.
    struct gamma g;
    g.C3 = NULL;
    g.B.C1 = NULL;
    g.B.C2 = NULL;
    g.B.port1 = -1;
    g.B.port2 = -1;
    g.port3 = -1;
    g.port4 = -1;
    return g;
}