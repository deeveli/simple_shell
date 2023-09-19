#include "shell.h"

/* Declaration of functions */
void handleSIGINT(void); // Declare handleSIGINT function
void check_command_chain(info_t *info, char *buffer, size_t *j, size_t i, size_t length);
int is_command_chain(info_t *info, char *buffer, size_t *j);
void _concatenate_strings(char **new_p, char *buffer, size_t len);
void _copy_string(char **new_p, char *buffer, size_t len);

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


ssize_t get_input(info_t *info)
{
	static char *buffer; 
	static size_t i, j, length;
	ssize_t bytes_read = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_commands(info, &buffer, &length);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (length) 
	{
		j = i; 
		p = buffer + i; 

		check_command_chain(info, buffer, &j, i, length);
		while (j < length) 
		{
			if (is_command_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= length) 
		{
			i = length = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p; 
		return (_strlen(p)); 
	}

	*buffer_p = buffer; 
	return (bytes_read); 
}


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


void handleSIGINT(void)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
