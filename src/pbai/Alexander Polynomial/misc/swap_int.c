/* Swaps two integers by value */
extern void swap_int(int* const a, int* const b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
