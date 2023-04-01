#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "parser.h"

int	dummy0(const char **text, unsigned int *index, void **data_struct, const rule_info_t *info)
{
    printf("hiiii <%s>\n", info->key);
    while (is_similar(info->keys, &(*text)[*index]))
        ++(*index);
    return 0;
}


int main()
{

const char *str = "On the other hand, we denounce with righteous indignation and dislike men who are so\
 beguiled and demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee \
 the pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty through weakness\
  of will, which is the same as saying through shrinking from toil and pain. These cases are perfectly simple and easy to\
   distinguish. In a free hour, when our power of choice is untrammelled and when nothing prevents our being able to do what\
    we like best, every pleasure is to be welcomed and every pain avoided. But in certain circumstances and owing to the claims \
    of duty or the obligations of business it will frequently occur that pleasures have to be repudiated and annoyances accepted. \
    The wise man therefore always holds in these matters to this principle of selection: he rejects pleasures to secure other greater\
     pleasures, or else he endures pains to avoid worse pains.";


    const rule_t *rules[] = {
        &(rule_t){.keys = (char *[]){" ", "\n", "a","b", "c", "d", "e", "f", "g", "h", "i","j","k","l","m","n", "o","p","r","s","t", "u","w", "x", "y","z",","},.fp = dummy0},
        NULL
    };

    parser(str, NULL, rules);
    return (0);
}