#include "main.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buffer[BUFFER_SIZE];
	size_t bytes_read;
	FILE *fp_from;
	FILE *fp_to;

	if (argc != 3)
	{
		printf("Usage: %s file_from file_to\n", argv[0]);
		exit(1);
	}

	fp_from = fopen(argv[1], "rb");

	if (fp_from == NULL)
	{
		printf("Error: Can't read from file %s\n", argv[1]);
		exit(1);
	}

	fp_to = fopen(argv[2], "wb");

	if (fp_to == NULL)
	{
		printf("Error: Can't write to file %s\n", argv[2]);
		exit(1);
	}


	bytes_read = 0;

	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp_from)) > 0)
	{
		fwrite(buffer, 1, bytes_read, fp_to);
	}

	if (fclose(fp_from) != 0)
	{
		printf("Error: Can't close file %s\n", argv[1]);
		exit(1);
	}

	if (fclose(fp_to) != 0)
	{
		printf("Error: Can't close file %s\n", argv[2]);
		exit(1);
	}
	return (0);
}
