#include "shell.h"

/**
 * print_error_string - Prints an input string to the error stream.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void print_error_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_error(str[i]);
		i++;
	}
}

/**
 * print_error - Writes the character c to the error stream.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_error(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_char_to_fd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_char_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_string_to_fd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int print_string_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += print_char_to_fd(*str++, fd);
	}
	return (i);
}