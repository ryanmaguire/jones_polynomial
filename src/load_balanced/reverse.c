#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "load_balanced.h"

void reverse(struct crossing *c) {
    struct crossing *temp;
    int n;

    /* swap opposite neighbors and swap c->ports indexing */
    temp = c->data[2];
    c->data[2] = c->data[0];
    c->data[0] = temp;

    temp = c->data[1];
    c->data[1] = c->data[3];
    c->data[3] = temp;

    int tempint;
    tempint = c->ports[2];
    c->ports[2] = c->ports[0];
    c->ports[0] = tempint;
    tempint = c->ports[1];
    c->ports[1] = c->ports[3];
    c->ports[3] = tempint;
    /* Make sure that ports connect correctly */
    for (n = 0; n < 4; n++) {
        c->data[n]->ports[c->ports[n]] = n;
    }

    /* flip direction */
    c->direction = (c->direction + 2) % 4;
}
