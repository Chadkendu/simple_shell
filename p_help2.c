#include "p_shell.h"

void logicOps(char *line, ssize_t *newLength);
void handleLine(char **line, ssize_t read);
ssize_t getNewLength(char *line);

/**
 * logicOps - Checks for logical operators "||" or "&&"
 *
 * Description:
 * @line: pointer to character to check
 * @newLength: Pointer to newLength in getNewLength function.
 */

void logicOps(char *line, ssize_t *newLength)
{
	char past, present, nex;

	past = *(line - 1);
	present = *line;
	next = *(line + 1);

	if (present == '&')
	{
		if (nex == '&' && past != ' ')
			(*newLength)++;
		else if (past == '&' && nex != ' ')
			(*newLength)++;
	}
	else if (present == '|')
	{
		if (nex == '|' && past != ' ')
			(*newLength)++;
		else if (past == '|' && nex != ' ')
			(*newLength)++;
	}
}

/**
 * get_newLength - Gets the new length of partitioned line
 * by ";", "||", "&&&", or "#"
 *
 * Description:
 * @line: line to check.
 *
 * Return: new length of the line.
 *
 */

ssize_t get_newLength(char *line)
{
	size_t b;
	ssize_t newLength = 0;
	char present, nex;

	for (b = 0; line[b]; b++)
	{
		present = line[b];
		nex = line[b + 1];
		if (present == '#')
		{
			if (b == 0 || line[b - 1] == ' ')
			{
				line[b] = '\0';
				break;
			}
		}
		else if (b != 0)
		{
			if (present == ';')
			{
				if (nex == ';' && line[b - 1] != ' ' && line[b - 1] != ';')
				{
					newLength += 2;
					continue;
				}
				else if (line[b - 1] == ';' && nex != ' ')
				{
					newLength += 2;
					continue;
				}
				if (line[b - 1] != ' ')
					newLength++;
				if (nex != ' ')
					newLength++;
			}
			else
				logicOps(&line[b], &newLength);
		}
		else if (present == ';')
		{
			if (b != 0 && line[b - 1] != ' ')
				newLength++;
			if (nex != ' ' && nex != ';')
				newLength++;
		}
		newLength++;
	}
	return (newLength);
}

/**
 * handleLine - Partitions line read from standard input
 *
 * Description:
 * @line: pointer to a line read from standard input.
 * @scan: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 * Replaces "#" with '\0'.
 */

void handleLine(char **line, ssize_t read)
{
	char *prev_line, *pres_line;
	char past, present, nex;
	size_t b, d;
	ssize_t newLength;

	newLength = get_newLength(*line);
	if (newLength == read - 1)
		return;
	pres_line = malloc(newLength + 1);
	if (!pres_line)
		return;
	d = 0;
	prev_line = *line;
	for (b = 0; prev_line[b]; b++)
	{
		present = prev_line[b];
		nex = prev_line[b + 1];
		if (b != 0)
		{
			past = prev_line[b - 1];
			if (present == ';')
			{
				if (nex == ';' && past != ' ' && past != ';')
				{
					pres_line[d++] = ' ';
					pres_line[d++] = ';';
					continue;
				}
				else if (past == ';' && nex != ' ')
				{
					pres_line[d++] = ';';
					pres_line[d++] = ' ';
					continue;
				}
				if (past != ' ')
					pres_line[d++] = ' ';
				pres_line[d++] = ';';
				if (nex != ' ')
					pres_line[d++] = ' ';
				continue;
			}
			else if (present == '&')
			{
				if (nex == '&' && past != ' ')
					pres_line[d++] = ' ';
				else if (past == '&' && nex != ' ')
				{
					pres_line[d++] = '&';
					pres_line[d++] = ' ';
					continue;
				}
			}
			else if (present == '|')
			{
				if (nex == '|' && past != ' ')
					pres_line[d++]  = ' ';
				else if (past == '|' && nex != ' ')
				{
					pres_line[d++] = '|';
					pres_line[d++] = ' ';
					continue;
				}
			}
		}
		else if (present == ';')
		{
			if (b != 0 && prev_line[b - 1] != ' ')
				pres_line[d++] = ' ';
			pres_line[d++] = ';';
			if (nex != ' ' && nex != ';')
				pres_line[d++] = ' ';
			continue;
		}
		pres_line[d++] = prev_line[b];
	}
	pres_line[d] = '\0';
	free(*line);
	*line = pres_line;
}
