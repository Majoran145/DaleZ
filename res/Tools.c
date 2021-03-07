#include <stdio.h>

char* concatenate(char* str1, char* str2, char erase1, char erase2)
{
	size_t i1 = 0;
	size_t i2 = 0;
	while (str1[i1])
	{
		i1++;
	}
	while (str2[i2])
	{
		i2++;
	}
	char* str = malloc(sizeof(char) * (i1 + i2 + 1));
	if (str)
	{
		size_t i = 0;
		while (i < i1)
		{
			str[i] = str1[i];
			i++;
		}
		i = 0;
		while (i< i2)
		{
			str[i1 + i] = str2[i];
			i++;
		}
		str[i1 + i2] = 0;
	}
	if (erase1)
	{
		free(str1);
	}
	if (erase2)
	{
		free(str2);
	}
	return(str);
}