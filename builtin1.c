#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, preceded
 *                  with line numbers starting at 0.
 * @info: Pointer to the info_t structure containing arguments.
 *
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias.
 * @info: Pointer to the info_t structure containing arguments.
 * @alias: The alias string to be removed.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *alias)
{
	char *equal_sign, original_char;
	int ret;

	equal_sign = _strchr(alias, '=');
	if (!equal_sign)
		return (1);
	original_char = *equal_sign;
	*equal_sign = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
	*equal_sign = original_char;
	return (ret);
}


int create_alias(info_t *info, char *alias)
{
	char *equal_sign;

	equal_sign = _strchr(alias, '=');
	if (!equal_sign)
		return (1);
	if (!*++equal_sign)
		return (remove_alias(info, alias));

	remove_alias(info, alias);
	return (add_node_end(&(info->alias), alias, 0) == NULL);
}


int print_single_alias(list_t *node)
{
	char *sign_position = NULL, *alias_string = NULL;

	if (node)
	{
		sign_position = _strchr(node->str, '=');
		for (alias_string = node->str; alias_string <= sign_position; alias_string++)
			_putchar(*alias_string);
		_putchar('\'');
		_puts(sign_position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


int manage_alias(info_t *info)
{
	int i = 0;
	char *sign_position = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_single_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		sign_position = _strchr(info->argv[i], '=');
		if (sign_position)
			create_alias(info, info->argv[i]);
		else
			print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}