/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_updated.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:14:35 by plesukja          #+#    #+#             */
/*   Updated: 2024/07/29 00:19:03 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
//#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static int	count_word(char *ptr, char c);
static int	add_word(char **result, char *str, char sep);
static char	*copy_word(char *src, int len);
static void	free_previous_allocated_word(char **result);

char	**ft_split(char const *s, char c)
{
	char	*ptr;
	int		word_count;
	char	**result;

	word_count = 0;
	if (!s)
		return (NULL);
	ptr = (char *)s;
	word_count = count_word(ptr, c);
	printf("Word count: %d\n", word_count);
	result = (char **)malloc((word_count + 1) * (sizeof(char *)));
	if (!result)
	{
		return (NULL);
	}
	if (add_word(result, ptr, c))
    {
        for (int i = 0; i < word_count; i++)
            printf("Result[%d]: %s\n", i, result[i]);
        return (result);
    }
	free_previous_allocated_word(result);
    free(result);
    return (NULL);
}

static int	count_word(char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != sep && (str[i + 1] == '\0' || str[i + 1] == sep))
			count++;
		i++;
	}
	return (count);
}

static int	add_word(char **result, char *str, char sep)
{
	int	i;
	int	word_index;
	int	word_len;

	i = 0;
	word_index = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			word_len = 0;
			while (str[i + word_len] && str[i + word_len] != sep)
				word_len++;
			result[word_index] = copy_word(&str[i], word_len);
			if (!result[word_index])
			{
				free_previous_allocated_word(result);
				free(result);
				return (0);
			}
			i += word_len;
			word_index++;
		}
		else
			i++;
	}
	result[word_index] = NULL;
	return (1);
}

static char	*copy_word(char *src, int len)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = src[i];
		i++;
	}
	word[len] = '\0';
	printf("Copied word: %s\n", word);
	return (word);
}

static void	free_previous_allocated_word(char **result)
{
	int	i;

	i = 0;
	while(result[i])
	{
		printf("Freeing word: %s\n", result[i]);
		free(result[i]);
		i++;
	}
}

int main(void)
{
    char **test = ft_split("0123,4", ',');

    if (!test)
    {
        printf("Error in ft_split\n");
        return 1;
    }
    for (int i = 0; test[i] != NULL; i++)
    {
        printf("TestResult[%d]: %s\n", i, test[i]);
    }
	free_previous_allocated_word(test);
	free(test);
    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>

static int ft_length(char const *s, char c) {
    size_t words = 0;
    for(size_t i = 0; s[i];) {
        for(; s[i] == c; i++);
        if (s[i] != c && s[i])
            words++;
        for(; s[i] != c && s[i]; i++);
    }
    return words;
}

char *ft_copy(const char *s, char c) {
    for(; *s && *s == c; s++);
    int i = 0;
    for(; s[i] && s[i] != c; i++);
    char *cpy = malloc(i + 1);
    if (!cpy)
        return NULL;
    i = 0;
    for(; s[i] && s[i] != c; i++)
        cpy[i] = s[i];
    cpy[i] = '\0';
    return cpy;
}

static void cleanup(char **cpy) {
    if(!cpy)
        return;
    for(int i = 0; cpy[i]; i++)
        free(cpy[i]);
    free(cpy);
}

char **ft_split(char const *s, char c) {
    if (!s && !c)
        return NULL;
    size_t count = ft_length(s, c);
    char **cpy = malloc(sizeof(char *) * (count + 1));
    if (!cpy)
        return NULL;
    size_t j = 0;
    for(size_t i = 0; s[i]; ) {
        for(; s[i] == c; i++);
        if (!s[i])
            break;
        cpy[j] = ft_copy(s + i, c);
        if (!cpy[j]) {
            cleanup(cpy);
            return NULL;
        }
        j++;
        for(; s[i] != c && s[i]; i++);
    }
    cpy[j] = NULL;
    return cpy;
}
/*
int main(void) {
    struct tests {
        char *str;
        char c;
    } tests[] = {
        {"hello!zzzzzzzz", 'z'},
        {"\t\t\t\thello!\t\t\t\t", '\t'},
        {"^^^1^^2a,^^^^3^^^^--h^^^^", '^'}
    };
    for(struct tests *t = tests; t < &tests[sizeof tests / sizeof *tests]; t++) {
        char **s = ft_split(t->str, t->c);
        if(!s)
            return 1;
        for(size_t i = 0; s[i]; i++)
            printf("%zu: %s\n", i, s[i]);
        cleanup(s);
    }
}
*/