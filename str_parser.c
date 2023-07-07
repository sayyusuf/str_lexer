#include "str_parser.h"
#include <stddef.h>

static inline int
cmp_key(const char *key, const char *text)
{
	if (!key || !text)
		return 0;
	while(*key)
	{
		if (*key != *text)
			return (*key - *text);
		++text;
		++key;
	}
	return (0);
}

static inline const char *
similar(const char **keys, const char *text)
{
	unsigned int	i;

	i = 0;
	while (keys[i])
	{
		if (!cmp_key(keys[i], text))
			return (keys[i]);
		++i;
	}
	return (NULL);
}

const char *
is_similar(const char **keys, const char *text)
{
	unsigned int	i;

	i = 0;
	while (keys[i])
	{
		if (!cmp_key(keys[i], text))
			return (keys[i]);
		++i;
	}
	return (NULL);
}


int
str_parser(const char *text, void *data_struct, const rule_t *rules[])
{
	unsigned int	i, n, f, ret;
	const char		*res;

	i = 0;
	while (text[i])
	{
		f = 1;
		n = 0;
		while (rules[n] && f)
		{
			res = similar((const char **)rules[n]->keys, &text[i]);
			if (res)
			{
				f = 0;
				ret = rules[n]->fp(&text, &i, data_struct, &(const rule_info_t){(char *)res, (char **)rules[n]->keys});
				if (ret)
					return (ret);
				break;
			}
			++n;
		}
		if (f)
			++i;
	}
	if (text[0])
		rules[0]->fp(&text, &i, data_struct, &(const rule_info_t){NULL, NULL});
	return (0);
}
