#ifndef STR_PARSER_H
#define STR_PARSER_H

#define	PARSER_ERROR		1

#define  PARSER_SUCCESS		0
#define  PARSER_CONTINUE	1
#define  PARSER_BREAK		2


#include <stddef.h>

typedef struct
{
	char *key;
	char **keys;
} rule_info_t;

typedef struct
{
	char	**keys;
	int	(*fp)(const char **text, unsigned int *index, void *data_struct, const rule_info_t *info);
} rule_t;


int
str_lexer(const char *text, void *data_struct, const rule_t *rules[], size_t *index);
const char *
is_similar(const char **keys, const char *text);

#endif
