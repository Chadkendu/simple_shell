#include "p_shell.h"

int p_strncmp(const char *sr1, const char *sr2, size_t w);
int p_strspn(char *sr, char *valid);
char *p_strchr(char *sr, char k);
int p_strcmp(char *sr1, char *sr2);

/**
 * p_strncmp - function to compare two strings
 *
 * Description:
 * @sr1:string pointer
 * @sr2: string pointer
 * @w: string byte to compare
 *
 * Return: <  0 sr1 shorter than sr2
 * 0 sr1 and s2 are same
 * > 0 sr1 longer than sr2
 */

int p_strncmp(const char *sr1, const char *sr2, size_t w)
{
	size_t b;

	for (b = 0; sr1[b] && sr2[b] && b < w; b++)
	{
		if (sr1[b] > sr2[b])
		{
			return (sr1[b] - sr2[b]);
		}
		else if (sr1[b] < sr2[b])
			return (sr1[b] - sr2[b]);
	}
	if (b == w)
		return (0);
	else
		return (-15);
}

/**
 * p_strcmp - function to compare two strings
 *
 * Description:
 * @sr1: first compared string
 * @sr2: second compared string
 *
 * Return: + byte difference if s1 > s2
 * 0 if s1 = s2
 * - byte difference if s1 < s2
 */

int p_strcmp(char *sr1, char *sr2)
{
	while (*sr1 && *sr2 && *sr1 == *sr2)
	{
		sr1++;
		sr2++;
	}

	if (*sr1 != *sr2)
	{
		return (*sr1 - *sr2);
	}

	return (0);
}

/**
 * p_strchr - Locates string character
 *
 * Description:
 * @sr: searched string
 * @k: character to locate
 *
 * Return: pointer to first occurence (k valid)
 * (k invalid) - NULL.
 */

char *p_strchr(char *sr, char k)
{
	int inDex;/** integer varible **/

	for (inDex = 0; sr[inDex]; inDex++)
	{
		if (sr[inDex] == k)
			return (sr + inDex);
	}
	return (NULL);
}

/**
 * p_strspn - finds substring length (prefix)
 *
 * Description:
 * @sr:searched string
 * @valid: measured string
 *
 * Return: number of bytes
 */

int p_strspn(char *sr, char *valid)
{
	int inDex;/** integer variable **/
	int bytes = 0;/** bytes **/

	while (*sr)
	{
		for (inDex = 0; valid[inDex]; inDex++)
		{
			if (*sr == valid[inDex])
			{
				bytes++;
				break;
			}
		}
		sr++;
	}
	return (bytes);
}
