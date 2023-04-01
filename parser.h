#ifndef PARSER_H
#define PARSER_H

typedef struct
{
	const char *key;
	const char **keys;
} rule_info_t;

typedef struct
{
	char	**keys;
	int	(*fp)(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info);
} rule_t;


int
parser(const char *text, void **data_struct, const rule_t *rules[]);
const char *
is_similar(const char **keys, const char *text);

#endif