#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "load_balanced.h"

struct crossing* next(struct crossing* c, int direction) {//Gives next crossing in given direction
    c->data[direction]->direction = (c->ports[direction]+2)%4; //Set direction of travel when next crossing is reached
    return c->data[direction];
}