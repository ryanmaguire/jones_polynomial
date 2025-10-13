#include "load_balanced.h"
void zerosmooth(struct knot k, struct crossing* c){
    c->data[0]->data[c->ports[0]] = c->data[1];//KILL crossing c!
    c->data[0]->ports[c->ports[0]] = c->ports[1];
    c->data[1]->data[c->ports[1]] = c->data[0];
    c->data[1]->ports[c->ports[1]] = c->ports[0];
    c->data[2]->data[c->ports[2]] = c->data[3];
    c->data[2]->ports[c->ports[2]] = c->ports[3];
    c->data[3]->data[c->ports[3]] = c->data[2];
    c->data[3]->ports[c->ports[3]] = c->ports[2];
    // Now, c is separated from the knot/link. Nothing points to it.
    // Now, we need to fix the orientations of the crossings.
    int check = 0;
    struct crossing *curr = c;
    int counter = 0;
    while (counter == 0){
        if (curr->direction == 0){
            reverse(curr);
        }
        if (curr->id == c->data[1]->id && (curr->direction == c->data[1]->direction || (curr->direction + 2) % 4 == c->data[1]->direction)){
            check = 1;
        }
        curr = next(curr,curr->direction);
        if ((curr->id == c->data[3]->id && curr->direction == c->data[3]->direction)){
            counter++;
        }
    }
    counter = 0;
    if (check == 0){
        curr = c->data[1];
        while (counter == 0){
        if (curr->direction == 0){
            reverse(curr);
        }
        curr = next(curr,curr->direction);
        if ((curr->id == c->data[0]->id && curr->direction == c->data[0]->direction)){
            counter++;
        }
    }
    }
}
void onesmooth(struct knot k, struct crossing *c){
    c->data[0]->data[c->ports[0]] = c->data[3];//KILL crossing c!
    c->data[0]->ports[c->ports[0]] = c->ports[3];
    c->data[3]->data[c->ports[3]] = c->data[0];
    c->data[3]->ports[c->ports[3]] = c->ports[0];
    c->data[2]->data[c->ports[2]] = c->data[1];
    c->data[2]->ports[c->ports[2]] = c->ports[1];
    c->data[1]->data[c->ports[1]] = c->data[2];
    c->data[1]->ports[c->ports[1]] = c->ports[2];
    // Now, c is separated from the knot/link. Nothing points to it.
    // Now, we need to fix the orientations of the crossings.
    int check = 0;
    struct crossing *curr = c;
    int counter = 0;
    while (counter == 0){
        if (curr->direction == 0){
            reverse(curr);
        }
        if (curr->id == c->data[3]->id && (curr->direction == c->data[3]->direction || (curr->direction + 2) % 4 == c->data[3]->direction)){
            check = 1;
        }
        curr = next(curr,curr->direction);
        if ((curr->id == c->data[1]->id && curr->direction == c->data[1]->direction)){
            counter++;
        }
    }
    counter = 0;
    if (check == 0){
        curr = c->data[3];
        while (counter == 0){
        if (curr->direction == 0){
            reverse(curr);
        }
        curr = next(curr,curr->direction);
        if ((curr->id == c->data[0]->id && curr->direction == c->data[0]->direction)){
            counter++;
        }
    }
    }
}
