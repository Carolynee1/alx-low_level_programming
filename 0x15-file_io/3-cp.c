#include "main.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * handle_error - Prints an error message and exits the program.
 *
 * @filename: The name of the file that caused the error.
 * @message: The error message to print.
 */

void handle_error(char *filename, char *message)
{
	printf("Error: %s %s\n", message, filename);
	exit(1);
}

FILE *open_file(char *filename, char *mode)
{
	FILE *fp = fopen(filename, mode);

	if (fp == NULL)

	{
		handle_error(filename, "Can't open file");
	}
	return (fp);
}

/**
 * main - Copies the contents of one file to another.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line arguments.
 *
 * Return: 0 on success, non-zero on failure.
 */

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
	fp_to = fopen(argv[2], "wb");


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
