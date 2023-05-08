#include "main.h"

/**
 * create_file - creates a new file and writes text content to it
 * @filename: the name of the file to create
 * @text_content: the text to write to the file
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd, bytes_written, num_letters;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (text_content == NULL)
	{
		close(fd);
		return (1);
	}

	{
		num_letters = strlen(text_content);

		bytes_written = write(fd, text_content, num_letters);

		if (bytes_written != num_letters)
		{
			close(fd);
			return (-1);
		}
	}

	close(fd);
	return (1);
}

