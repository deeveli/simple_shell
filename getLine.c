#include "shell.h"

/* Declaration of functions */
void handleSIGINT(void); /*Declare handleSIGINT function*/
void check_command_chain(info_t *info, char *buffer, size_t *j, size_t i, size_t length); /* Declare check_command_chain function*/
int is_command_chain(info_t *info, char *buffer, size_t *j); /* Declare is_command_chain function*/
void _concatenate_strings(char **new_p, char *buffer, size_t len); /* Declare _concatenate_strings function*/
void _copy_string(char **new_p, char *buffer, size_t len); /* Declare _copy_string function*/

/**
 * buffer_commands - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t buffer_commands(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSIGINT);
#if USE_GETLINE
		bytes_read = getline(buffer, &length_p, stdin);
#else
		bytes_read = _getline(info, buffer, &length_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = bytes_read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - gets a line without the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t bytes_read = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_commands(info, &buffer, &length);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to the current buffer position */
		p = buffer + i; /* get pointer for return */

		check_command_chain(info, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_command_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached the end of the buffer? */
		{
			i = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p; /* pass back pointer to the current command position */
		return (_strlen(p)); /* return the length of the current command */
	}

	*buffer_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (bytes_read); /* return the length of the buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);
	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return (bytes_read);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of the preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (i == len)
		i = len = 0;

	bytes_read = read_buffer(info, buffer, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? (free(p), -1) : -1);

	if (size)
		_concatenate_strings(&new_p, buffer + i, k - i);
	else
		_copy_string(&new_p, buffer + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * handleSIGINT - blocks ctrl-C
 */
void handleSIGINT(void)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}