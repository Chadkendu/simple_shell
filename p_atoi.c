#include "p_shell.h"

/**
 * p_atoi - changes string to an integer
 *
 * Description:
 * @str: string pointer
 *
 * Return: no string no(0), string no(1)
 *
 */

int p_atoi(char *str)
{
	int idx = 0; /** index var for string iterating **/
	int multiplier = 1;/** negative value var **/
	int digit_found = 0;/** flag variable to indicate if found **/
	unsigned int number = 0;/** var to stroe the resulting int value **/

	for (; str[idx]; idx++)
	{
		/** check if current char is negav sign **/
		if (str[idx] == '-')
		{
			multiplier *= -1; /** ensures @number get the right sign **/
		}
		while (str[idx] >= '0' && str[idx] <= '9')
		{
			digit_found = 1;
			number = (number * 10) + (str[idx] - '0');
			idx++;
		}
		if (digit_found == 1)
			break; /** ensures digit after non-digit aren't computed **/
		idx++;
	}
	number *= multiplier;
	return (number);
}
