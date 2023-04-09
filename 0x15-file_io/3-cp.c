#include "main.h"
#include <errno.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int open_file_for_reading(char *filename);
int source_fd = open_file_for_reading(argv[1]);
int open_file_for_writing(char *filename);
int copy_file(int source_fd, int dest_fd);
int close_file(int fd);
void set_permissions(char *filename);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	int source_fd = open_file_for_reading(argv[1]);
	int dest_fd = open_file_for_writing(argv[2]);

	if (copy_file(source_fd, dest_fd) == -1)
	{
		exit(99);
	}

	set_permissions(argv[2]);

	if (close_file(source_fd) == -1)
	{
		exit(100);
	}

	if (close_file(dest_fd) == -1)
	{
		exit(100);
	}

	return (0);
}

int open_file_for_reading(char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd == -1)

	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
		exit(98);
	}
	return (fd);
}

int open_file_for_writing(char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);

	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
		exit(99);
	}
	return (fd);
}

int copy_file(int source_fd, int dest_fd)
{
	ssize_t bytes_read;
	char buffer[BUFFER_SIZE];

	while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0)

	{
		ssize_t bytes_written = write(dest_fd, buffer, bytes_read);

		if (bytes_written == -1 || bytes_written != bytes_read)

		{
			dprintf(STDERR_FILENO, "Error: Can't write
					to file descriptor %d\n", dest_fd);
			return (-1);
		}
	}
	if (bytes_read == -1)
	{

		dprintf(STDERR_FILENO, "Error: Can't read from
				file descriptor %d\n", source_fd);
		return (-1);
	}
	return (0);
}

int close_file(int fd)
{
	int result = close(fd);

	if (result == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		return (-1);
	}
	return (0);
}

void set_permissions(char *filename)
{
	int result = chmod(filename, 0600);

	if (result == -1 && errno != EEXIST)
	{
		dprintf(STDERR_FILENO, "Error: Can't set permissions for %s\n",
