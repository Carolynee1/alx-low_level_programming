#include "main.h"

/**
 * read_textfile - reads a text file and prints it to the POSIX stdout
 * @filename: points the name of file
 * @letters: the number of letters the function should read
 * and print
 * Return: if function fails or filename is NULL - 0,
 * or if the actual  no of bytes the function can read or print
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	int t, o, p;
	char *buf;

	if (filename == NULL)
	{
		return (0);
	}

	t = open(filename, O_RDONLY);
	if (t == -1)
	{
		return (0);
	}

	buf = malloc(letters * sizeof(char));
	if (buf == NULL)
	{
		close(t);
		return (0);
	}

	o = read(t, buf, letters);
	if (o == -1)
	{
		free(buf);
		close(t);
		return (0);
	}

	p = write(STDOUT_FILENO, buf, o);
	if (p == -1 || p != o)
	{
		free(buf);
		close(t);
		return (0);
	}

	free(buf);
	close(t);
	return (o);
}
