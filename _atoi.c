#include "shell.h"

/**
 * interactive - Check if the program is running interactively.
 *
 * @info: A pointer to the info_t structure containing program context.
 * Return: 1 if running interactively, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Check if a character is a delimiter.
 *
 * @c: The character to check.
 * @delim: A pointer to a null-terminated string of delimiter characters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}


int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}


int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}
	return (output);
}