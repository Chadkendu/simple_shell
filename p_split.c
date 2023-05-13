#include "p_shell.h"

char **p_strtok(char *strg, char *delimiter);
int countToken(char *strg, char *delimiter);
int tokenLen(char *strg, char *delimiter);

/**
 * countToken - function to count the numbers of token in a string
 *
 * Description:
 * @strg: string pointer
 * @delimiter: delimiter pointer
 *
 * Return: words number within strg
 *
 */

int countToken(char *strg, char *delimiter)
{
	int b, numbToken = 0, strglen = 0;

	/** calculate string length **/
	for (b = 0; *(strg + b); b++)
	{
		strglen++;
	}

	/** iterate through the string and count token number **/
	for (b = 0; b < strglen; b++)
	{
		/** if not delimiter, increment token count **/
		if (*(strg + b) != *delimiter)
		{
			numbToken++;
			/** skip the current token to avoid repeat **/
			b += tokenLen(strg + b, delimiter);
		}
	}
	return (numbToken);
}

/**
 * tokenLen - function to locate delimeter index
 *
 * Description:
 * @strg: searched string
 * @delimiter: character delimiter
 *
 * Return: index of delimiter
 *
 */

int tokenLen(char *strg, char *delimiter)
{
	int b = 0, token_len = 0;

	/** iterate the string till delimiter is found or end of string **/
	while (*(strg + b) && *(strg + b) != *delimiter)
	{
		token_len++;
		b++;
	}
	return (token_len);
}

/**
 * p_strtok - function to tokenize a string
 *
 * Description:
 * @strg: string
 * @delimiter: character delimiter
 *
 * Return: pointer to tokenized array
 *
 */

char **p_strtok(char *strg, char *delimiter)
{
	char **tokens;
	int index = 0, numbToken, t, letters, l;

	/** count token string **/
	numbToken = countToken(*strg, delimiter);
	if (numbToken == 0)
		return (NULL);
	/** allocate memory for token array **/
	tokens = malloc(sizeof(char *) * (numbToken + 2));
	if (!tokens)
		return (NULL);

	for (t = 0; t < numbToken; t++)
	{
		while (strg[index] == *delimiter)
			index++;
		letters = tokenLen(strg + index, delimiter);
		/** allocate memory for token **/
		tokens[t] = malloc(sizeof(char) * (letters + 1));
		if (!tokens[t])
		{
			for (index - = 1; index >= 0; index--)
				free(tokens[index]);
			free(tokens);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			tokens[t][l] = strg[index];
			index++;
		}
		tokens[t][l] = '\0';
	}
	tokens[t] = NULL;/** set last two element to NULL **/
	tokens[t + 1] = NULL;

	return (tokens);
}
