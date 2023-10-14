#include "simshell.h"

char *strdup_func(const char *s);
char *strncat_sim(char *dest, char *src, int n);
size_t strspn_sim(char *s, char *accept);
int strncmp_sim(const char *s1, const char *s2, int n);
char *strncpy_sim(char *dest, char *source, int n);
int atoi_sim(char *s);

/**
* strdup_func - Entry point
* Desc - 'a function that duplicates a string including allocating
* memory dynamically'
* @s: string to be duplicated
*
* Return: a pointer to the duplicated string
*/

char *strdup_func(const char *s)
{
int z = 0;
char *copy;
int len = 0;


if (s == NULL)
{
return (NULL);
}


while (s[len] != '\0')
{
len++;
}


copy = malloc((len + 1) * sizeof(char));
if (copy == NULL)
{
/* if memory allocation fails */
return (NULL);
}

for (z = 0; z < len; z++)
{
copy[z] = s[z];
}
copy[z] = '\0';
return (copy);
}
/**
* strncat_sim - Entry point
* Desc - 'a function used to concantenate a specified number of chars'
* @src: a pointer to the source string
* @dest: a pointer to the destination string
* @n: the maximum number of chars to be concantenated
*
* Return: pointer to dest
*/


char *strncat_sim(char *dest, char *src, int n)
{
int dest_len = strlen_sim(dest);


int z;


for (z = 0; z < n && src[z] != '\0'; z++)
{
dest[dest_len + z] = src[z];
}
dest[dest_len + z] = '\0';


return (dest);


}
/**
* strspn_sim - Entry point
* Desc - ' a function that gets the length of a prefix substring'
* @s: string to be checked
* @accept: the substring to be checked
*
* Return: the number of bytes within s that only belongs to accept
*/


size_t strspn_sim(char *s, char *accept)
{
size_t k, z;


for (k = 0; s[k] != '\0'; k++)
{
for (z = 0; accept[z] != '\0'; z++)
{
if (s[k] == accept[z])
{
break;
}
}
if (accept[z] == '\0')
{
break;
}
}
return (k);
}
/**
* strncmp_sim - Entry point
* Desc - ' a function that compares two strings according to a specif-
* ' ied number of bytes or characters'
* @s1: pointer to a string
* @s2: pointer to another string
* @n: specified or maximum number of bytes to be used for comparing
*
* Return: if value is less than 0, then s1 is shorter or less than s2
* if value is 0 then s1 and s2 are the same or have a match
* if value is greater than 0, then s2 is longer than s1
*/


int strncmp_sim(const char *s1, const char *s2, int n)
{
int z = 0;


/* an iterator that keeps count of bytes or characters*/


while (s1[z] && s2[z] && z < n)
{
if (s1[z] != s2[z])
{
return (s1[z] - s2[z]);
}
z++;
}


if (z == n)
{
return (0);
}


if (s1[z] && !s2[z])
{
return (1);
}
else if (!s1[z] && s2[z])
{
return (-1);
}


return (0);
}
/**
* strncpy_sim - Entry point
* Desc -'a function that copies a string'
* @dest: destination char string type
* @source: initial char string type
* @n: maximum number of bytes to be used
* Return: pointer to destination
*/

char *strncpy_sim(char *dest, char *source, int n)
{
	int cobli;

	for (cobli = 0; cobli < n && source[cobli] != '\0'; cobli++)
	{
		dest[cobli] = source[cobli];
	}
	for (; cobli < n; cobli++)
	{
		dest[cobli] = '\0';
	}
	return (dest);

}
/**
 * atoi_sim - Entry point
 * Desc -'funtion that converts a chracter string to an integer'
 * @s: the string to be converted
 * Return: converted interger value
 */
int atoi_sim(char *s)
{
	int resi_val = 0;
	int sn = 1;
	int k = 0;

	while (s[k] == ' ' || s[k] == '\t' || s[k] == '\n')
	{
		k++;
	}

	if (s[k] == '+' || s[k] == '-')
	{
		sn = (s[k++] == '-') ? -1 : 1;
	}

	while (s[k] >= '0' && s[k] <= '9')
	{
		resi_val = resi_val * 10 + (s[k] - '0');
		k++;
	}

return (resi_val * sn);
}
