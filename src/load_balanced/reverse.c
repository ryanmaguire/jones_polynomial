#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "load_balanced.h"

void reverse(struct crossing c) {
    struct crossing *temp;
    temp = c.data[2];
    c.data[2] = c.data[0];
    c.data[0] = temp;
    temp = c.data[1];
    c.data[1] = c.data[3];
    c.data[3] = temp;
    if (c.direction == 0) {
        c.direction = 2;
    }
    else if (c.direction == 1) {
        c.direction = 3;
    }
    else if (c.direction == 2) {
        c.direction = 0;
    }
    else if (c.direction == 3) {
        c.direction = 1;
    }
}