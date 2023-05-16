#include "p_shell.h"

void alias_print(alias_t *alias);
char **alias_replace(char **args);
int parv_alias(char **args, char __attribute__((__unused__)) **ahead);
void alias_set(char *varName, char *value);

/**
 * alias_set - set alias with new value or make a new one
 *
 * Description:
 * @varName: alias name
 * @value: alias value. First character ('=')
 *
 * Return: void
 */

void alias_set(char *varName, char *value)
{
	alias_t *temp = aliaz;
	int length, d, e;
	char *newValue;

	*value = '\0';
	value++;
	length = p_strlent(value) - p_strspn(value, "'\"");
	newValue = malloc(sizeof(char) * (length + 1));
	if (!newValue)
		return;
	for (d = 0, e = 0; value[d]; d++)
	{
		if (value[d] != '\'' && value[d] != '"')
			newValue[e++] = value[d];
	}
	newValue[e] = '\0';
	while (temp)
	{
		if (p_strcmp(varName, temp->name) == 0)
		{
			free(temp->value);
			temp->value = newValue;
			break;
		}
		temp = temp->nex;
	}
	if (!temp)
		core_add(&aliaz, varName, newValue);
}

/**
 * parv_alias - print all alias, create a new alias
 *
 * Description:
 * @args: array of arguments.
 * @ahead: double pointer to args beginning
 *
 * Return: error (-1), success (0)
 */

int parv_alias(char **args, char __attribute__((__unused__)) **ahead)
{
	alias_t *temp = aliaz;
	int b, exitStat = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			alias_print(temp);
			temp = temp->nex;
		}
		return (exitStat);
	}
	for (b = 0; args[b]; b++)
	{
		temp = aliaz;
		value = p_strchr(args[b], '=');
		if (!value)
		{
			while (temp)
			{
				if (p_strcmp(args[b], temp->name) == 0)
				{
					alias_print(temp);
					break;
				}
				temp = temp->nex;
			}
			if (!temp)
				exitStat = err_create(args + b, 1);
		}
		else
			alias_set(args[b], value);
	}
	return (exitStat);
}

/**
 * alias_print - dispaly alias format name = 'value'
 *
 * Description:
 * @alias: Pointer to alias
 *
 * Return: void
 */

void alias_print(alias_t *alias)
{
	char *stringAliaz;
	int length = p_strlent(alias->name) + p_strlent(alias->val) + 4;

	stringAliaz = malloc(sizeof(char) * (length + 1));
	if (!stringAliaz)
		return;
	p_strcpy(stringAliaz, alias->name);
	p_strcat(stringAliaz, "='");
	p_strcat(stringAliaz, alias->val);
	p_strcat(stringAliaz, "'\n");

	write(STDOUT_FILENO, stringAliaz, length);
	free(stringAliaz);
}

/**
 * alias_replace - scans argument and replace alias with value
 *
 * Description:
 * @args: pointer to arguments.
 *
 * Return: pointer to arguments.
 */

char **alias_replace(char **args)
{
	alias_t *temp;
	int b;
	char *newValue;

	if (p_strcmp(args[0], "alias") == 0)
		return (args);
	for (b = 0; args[b]; b++)
	{
		temp = aliaz;
		while (temp)
		{
			if (p_strcmp(args[b], temp->name) == 0)
			{
				newValue = malloc(sizeof(char) * (p_strlent(temp->val) + 1));
				if (!newValue)
				{
					args_free(args, args);
					return (NULL);
				}
				p_strcpy(newValue, temp->val);
				free(args[b]);
				args[b] = newValue;
				b--;
				break;
			}
			temp = temp->net;
		}
	}
	return (args);
}
