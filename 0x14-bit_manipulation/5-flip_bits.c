#include "main.h"

/**
 * flip_bits - returns the number of bits to flip to get from n to m
 * @n: first unsigned long int to compare
 * @m: second unsigned long int to compare
 * Return: the number of bits that differ between n and m
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int xor_result;
	unsigned int num_bits_to_flip = 0;

	xor_result = n ^ m;

	while (xor_result > 0)
	{
		if ((xor_result & 1) == 1)
			num_bits_to_flip++;
		xor_result = xor_result >> 1;
	}

	return (num_bits_to_flip);
}
