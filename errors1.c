#include "shell.h"

/**
 * convert_string_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int convert_string_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - prints an error message.
 * @info: the parameter and return info struct.
 * @error_string: string containing the specified error type.
 * Return: Nothing.
 */
void print_error_message(info_t *info, char *error_string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_integer(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * print_integer - prints a decimal (integer) number (base 10).
 * @input: the input.
 * @fd: the file descriptor to write to.
 *
 * Return: number of characters printed.
 */
int print_integer(int input, int fd)
{
	int (*print_char_func)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		print_char_func = _eputchar;
	if (input < 0)
	{
		absolute = -input;
		print_char_func('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			print_char_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char_func('0' + current);
	count++;

	return (count);
}

/**
 * convert_number_to_string - converter function, a clone of itoa.
 * @num: number.
 * @base: base.
 * @flags: argument flags.
 *
 * Return: string.
 */
char *convert_number_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments_from_string - function replace fist instance
 * @str: address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_comments_from_string(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '#' && (!i || str[i - 1] == ' '))
		{
			str[i] = '\0';
			break;
		}
}