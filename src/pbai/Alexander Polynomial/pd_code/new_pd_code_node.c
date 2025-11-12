#include <stdlib.h>
#include "pd_code_knot.h"

/* Returns a pointer to a new pd_code_node struct */
extern struct pd_code_node* new_pd_code_node(struct crossing* C)
{
	struct pd_code_node* result = malloc(sizeof(struct pd_code_node));
	if (!result) {
		return NULL;
	}
	result->tuple = C;
	result->next = (void*)0;
	result->prev = (void*)0;
	return result;
}