#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "parser.h"
#include <string.h>


int	dummy_empty(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info)
{
	(void)data_struct;
    char s[255];

    strncpy(s, *text, *index);
    s[*index] = 0;
    if (*index)
        printf("1<%s>\n", s);
    (*text) += *index;
    *index = 0;
    return 0;
}

int	folder_opt(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info)
{
    (void)data_struct;
    char s[255];

    strncpy(s, *text, *index);
    s[*index] = 0;
    if (*index)
        printf("1<%s>\n", s);
    printf("1<%s>\n", info->key);
    (*text) += *index + strlen(info->key);
    *index = 0;
    return 0;
}

int	dummy0(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info)
{
	(void)data_struct;
    char s[255];
    const char *str;
    strncpy(s, *text, *index);
    s[*index] = 0;
    if (*index)
        printf("<%s>\n", s);

    str = info->key;
    do {
        (*index) += strlen(str);
        str = (is_similar((const char **)info->keys, &(*text)[*index]));
    } while (str);
    (*text) += *index;
    *index = 0;
    return 0;
}

int	dummy1(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info)
{
	(void)data_struct;
    char s[255];
    strncpy(s, *text, *index);
    s[*index] = 0;
    if (*index)
        printf("1<%s>\n", s);
    printf("1<%s>\n", info->key);
    (*text) += *index + strlen(info->key);
    *index = 0;
    return 0;
}

int	double_quote_rule(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info)
{
	(void)data_struct;
    char s[255];
    unsigned int i;

    i = *index + strlen(info->key);

    while ((*text)[i] && !is_similar((const char **)info->keys, &(*text)[i]))
        i += strlen(info->key);
    if (!(*text)[i])
        return -1;
    i += strlen(info->key);
    strncpy(s, *text, i);
    s[i] = 0;
    if (i)
        printf("2<%s>\n", s);
    (*text) += i+ strlen(info->key);
    *index = 0;
    return 0;
}




int main()
{

const char *str = "On <  <<   *******\"the other hand,,.  \"  we denounce with righteous indignation and dislike men who are so\
 beguiled and demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee \
 the pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty through weakness\
  of will, which is the same as saying through shrinking from toil and pain. These cases are perfectly simple and easy to\
   distinguish. In a free hour, when our power of choice is untrammelled and when nothing prevents our being able to do what\
    we like best, every pleasure is to be welcomed and every pain avoided. But in certain circumstances and owing to the claims \
    of duty or the obligations of business it will frequently occur that pleasures have to be repudiated and annoyances accepted. \
    The wise man therefore always holds in these matters to this principle of selection: he rejects pleasures to secure other greater\
     pleasures, or else he endures pains to avoid worse pains. hi";


    const rule_t *rules[] = {
        &(rule_t){.keys = (char *[]){ NULL}, .fp = dummy_empty},
        &(rule_t){.keys = (char *[]){ "<<", ">>", "<", ">", "(", ")", "||", "|", "&&", "&", "=", NULL}, .fp = folder_opt},
        &(rule_t){.keys = (char *[]){" ", "\n", NULL}, .fp = dummy0},
        &(rule_t){.keys = (char *[]){",",".", NULL}, .fp = dummy1},
        &(rule_t){.keys = (char *[]){"\"", NULL}, .fp = double_quote_rule},
        NULL
    };


    parser(str, NULL, rules);
    return (0);
}

