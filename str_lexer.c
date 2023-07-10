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
str_lexer(const char *text, void *data_struct, const rule_t *rules[], size_t *index)
{
	unsigned int	i, n, f;
	int				ret;
	const char		*res;
	const char		*save;

	i = 0;
	save = text;
	while (text[i])
	{
		n = 0;
		f = 1;
		while (rules[n] && f)
		{
			res = similar((const char **)rules[n]->keys, &text[i]);
			if (res)
			{
				ret = rules[n]->fp(&text, &i, data_struct, &(const rule_info_t){(char *)res, (char **)rules[n]->keys});
				switch (ret)
				{
					case PARSER_SUCCESS:
						f = 0;
						break;
					case PARSER_CONTINUE:
						break;
					case PARSER_BREAK:
						*index = &text[i] - save;
						return (PARSER_BREAK);
					default:
						*index = &text[i] - save;
						return (ret);
				}
			}
			++n;
		}
		if (f)
			++i;
	}
	if (text[0])
		rules[0]->fp(&text, &i, data_struct, &(const rule_info_t){NULL, NULL});
	*index = &text[i] - save;
	return (0);
}
