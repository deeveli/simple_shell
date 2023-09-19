#include "shell.h"

/**
 * copy_string - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @num: the number of characters to be copied
 * Return: the pointer to the destination string
 */
char *copy_string(char *destination, char *source, int num)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < num - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}


char *concatenate_strings(char *destination, char *source, int num)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < num)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < num)
		destination[i] = '\0';
	return (result);
}


char *locate_character(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
