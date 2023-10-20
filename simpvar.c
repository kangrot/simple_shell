#include "simpshell.h"

int simp_is_chain(info_t *info, char *b, size_t *z);
void simp_check_chain(info_t *info, char *b,
		size_t *p, size_t z, size_t lent);
int rep_alias(info_t *info);
int rep_vars(info_t *info);
int rep_stri(char **o_stri, char *n_stri);

/**
 * simp_is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @b: the char buffer
 * @z: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int simp_is_chain(info_t *info, char *b, size_t *z)
{
	size_t j = *z;

	if (b[j] == '|' && b[j + 1] == '|')
	{
		b[j] = 0;
		j++;
		info->cmmd_buff_type = CMD_OR;
	}
	else if (b[j] == '&' && b[j + 1] == '&')
	{
		b[j] = 0;
		j++;
		info->cmmd_buff_type = CMD_AND;
	}
	else if (b[j] == ';') /* found end of this command */
	{
		b[j] = 0; /* replace semicolon with null */
		info->cmmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*z = j;
	return (1);
}

/**
 * simp_check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @b: the char buffer
 * @p: address of current position in buf
 * @z: starting position in buf
 * @lent: length of buf
 *
 * Return: Void
 */
void simp_check_chain(info_t *info, char *b, size_t *p, size_t z, size_t lent)
{
	size_t j = *p;

	if (info->cmmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			b[z] = 0;
			j = lent;
		}
	}
	if (info->cmmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			b[z] = 0;
			j = lent;
		}
	}

	*p = j;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *info)
{
	int z = 0;
	list_t *node;
	char *q;

	while (z < 10)
	{
		node = nod_starts(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		q = simp_strchr(node->str, '=');
		if (!q)
			return (0);

		q = simp_strdup(q + 1);
		if (!q)
			return (0);

		info->argv[0] = q;
		z++;
	}
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *info)
{
	int z = 0;
	list_t *node;

	for (z = 0; info->argv[z]; z++)
	{
		if (info->argv[z][0] != '$' || !info->argv[z][1])
			continue;

		if (!simp_strcmp(info->argv[z], "$?"))
		{
			rep_stri(&(info->argv[z]),
				simp_strdup(conv_num(info->status, 10, 0)));
			continue;
		}
		if (!simp_strcmp(info->argv[z], "$$"))
		{
			rep_stri(&(info->argv[z]),
				simp_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = nod_starts(info->env, &info->argv[z][1], '=');
		if (node)
		{
			rep_stri(&(info->argv[z]),
				simp_strdup(simp_strchr(node->str, '=') + 1));
			continue;
		}
		rep_stri(&info->argv[z], simp_strdup(""));

	}
	return (0);
}

/**
 * rep_stri - replaces string
 * @o_stri: address of old string
 * @n_stri: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_stri(char **o_stri, char *n_stri)
{
	free(*o_stri);
	*o_stri = n_stri;
	return (1);
}
