#include "p_shell.h"

/**
 * list_free - free linkedlist
 *
 * Description:
 * @top: the top of link_t list
 *
 * Return: void
 *
 */

void list_free(link_t *top)
{
	link_t *net;

	while (top)
	{
		net = top->net;
		free(top->dir);
		free(top);
		top = net;
	}
}

/**
 * aliasend_add - Adds node to end of alias_t linked list
 *
 * Description:
 * @top: pointer to head of the link_t list.
 * @name: name of new alias to add
 * @value: value of new alias to add
 *
 * Return: error (NULL), 0 pointer to new node.
 */

alias_t *aliasend_add(alias_t **top, char *name, char *value)
{
	alias_t *newCore = malloc(sizeof(alias_t));
	alias_t *last;

	if (!newCore)
		return (NULL);

	newCore->net = NULL;
	newCore->name = malloc(sizeof(char) * (p_strlent(name) + 1));
	if (!newCore->name)
	{
		free(newCore);
		return (NULL);
	}
	newCore->value = value;
	p_strcpy(newCore->name, name);

	if (*top)
	{
		last = *top;
		while (last->net != NULL)
			last = last->nex;
		last->net = newCore;
	}
	else
		*top = newCore;

	return (newCore);
}

/**
 * alias_freelist - Frees alias_t linked list
 *
 * Description:
 * @top: THe top of the alias_t list
 *
 * Return: void
 *
 */

void alias_freelist(alias_t *top)
{
	alias_t *nex;

	while (top)
	{
		net = top->nex;
		free(top->name);
		free(top->value);
		free(top);
		top = nex;
	}
}

/**
 * core_add - Adds node to end of a link_t linked list.
 *
 * Description:
 * @top: pointer to top of the link_t list
 * @dir: directory path for the new core
 *
 * Return: If an error (NULL) , else pointer to the new core
 */

link_t *core_add(link_t **top, char *dir)
{
	link_t *newCore = malloc(sizeof(link_t));
	link_t *last;

	if (!newCore)
		return (NULL);

	newCore->dir = dir;
	newCore->nex = NULL;

	if (*top)
	{
		last = *top;
		while (last->nex != NULL)
			last = last->nex;
		last->nex = newCore;
	}
	else
		*top = newCore;

	return (newCore);
}
