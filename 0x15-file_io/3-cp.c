#include "main.h"

#define BUFFER_SIZE 1024

/**
 * h_err - displays an error message and exits
 * main - copies the content of a file to another file.
 * the program with an error code
 *
 * @message: The error message to print.
 *
 * Return: None
 */

void h_err(char *message);

int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		h_err("Can't write to file");
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);

	if (fd_to == -1)
	{
		h_err("Can't write to file");
	}

	while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);

		if (bytes_written == -1 || bytes_written != bytes_read)

		{
			h_err("Can't write to file");
		}

	}
	if (bytes_read == -1)
	{
		h_err("Can't read from file");
	}

	return (EXIT_SUCCESS);
}

void h_err(char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}
