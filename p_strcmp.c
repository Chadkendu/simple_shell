#include "p_shell.h"

/**
 * p_strcmp - function to compare two string
 * and returns an integer value indicating
 * whether they are equal or not
 *
 * Description:
 * @sr1: string uno(first)
 * @sr2: string duo(second)
 *
 * Return: if string the same (0), if string not the same (1)non zero
 *
 */

int p_strcmp(char *sr1, char *sr2)
{
	int b; /** to iterate through string **/

	/** iterate untile end of string is reahced **/
	for (b = 0; sr1[b] != '\0' && sr2[b] != '\0'; b++)
	{
		if (sr1[b] != sr2[b])
		{
			/** if char is in cureent pos and string not equa, return 1 **/
			return (1);
		}
	}
	if (sr1[b] != sr2[b])
	{
		return (1);
	}
	return (0);
}
