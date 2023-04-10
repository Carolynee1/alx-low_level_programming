#include "main.h"
#include <stdio.h>
#include <errno.h>

#define BUFSIZE 1024

void print_error(char *error_message, char *filename, int exit_code)
{
	dprintf(STDERR_FILENO, error_message, filename);
	exit(exit_code);
}

int main(int argc, char **argv)
{
	int fd_from, fd_to;
	char buf[BUFSIZE];
	ssize_t bytes_read, bytes_written;

	/* Check for correct number of arguments */
	if (argc != 3)
		print_error("Usage: cp file_from file_to\n", "", 97);

	/* Open file_from for reading */
	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		print_error("Error: Can't read from file %s\n", argv[1], 98);

	/* Open file_to for writing (truncating if it already exists) */
	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
		print_error("Error: Can't write to %s\n", argv[2], 99);

	/* Copy contents of file_from to file_to */
	while ((bytes_read = read(fd_from, buf, BUFSIZE)) > 0)
	{
		bytes_written = write(fd_to, buf, bytes_read);
		if (bytes_written == -1)
			print_error("Error: Can't write to %s\n", argv[2], 99);
	}

	/* Check for errors in reading or writing */
	if (bytes_read == -1)
		print_error("Error: Can't read from file %s\n", argv[1], 98);

	/* Close file descriptors */
	if (close(fd_from) == -1)
		print_error("Error: Can't close fd %d\n", int fd_from, 100);
	if (close(fd_to) == -1)
		print_error("Error: Can't close fd %d\n", int fd_to, 100);

	return 0;
}

