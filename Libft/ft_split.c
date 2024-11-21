/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:00:58 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/16 13:00:03 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_putword(char *word, const char *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

/* splits *s by delimiter c, storing count number of split words in **strings*/

static char	**ft_split_enter(const char *s, char c, char **strings, int count)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < count)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		strings[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (strings == NULL)
			return (free_array(strings, word));
		ft_putword(strings[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	strings[word] = 0;
	return (strings);
}

char	**ft_split(const char *s, char c)
{
	char			**strings;
	unsigned int	count;

	if (s == NULL)
		return (NULL);
	count = ft_count_words(s, c);
	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (strings == NULL)
		return (NULL);
	strings = ft_split_enter(s, c, strings, count);
	return (strings);
}
/*
#include <stdio.h>

int main() {
    const char *input1 = "Hello World! This is a test.";
    const char *input2 = "Split,this,string,using,comma";
    const char *input3 = "NoDelimitersHere";
    const char *input4 = "SingleDelimiter";
    const char *input5 = "";

    char **words1 = ft_split(input1, ' ');
    printf("Words from input1:\n");
    for (int i = 0; words1[i] != NULL; i++) {
        printf("%s\n", words1[i]);
    }
    printf("\n");

    char **words2 = ft_split(input2, ',');
    printf("Words from input2:\n");
    for (int i = 0; words2[i] != NULL; i++) {
        printf("%s\n", words2[i]);
    }
    printf("\n");

    char **words3 = ft_split(input3, ' ');
    printf("Words from input3:\n");
    for (int i = 0; words3[i] != NULL; i++) {
        printf("%s\n", words3[i]);
    }
    printf("\n");

    char **words4 = ft_split(input4, ' ');
    printf("Words from input4:\n");
    for (int i = 0; words4[i] != NULL; i++) {
        printf("%s\n", words4[i]);
    }
    printf("\n");

    char **words5 = ft_split(input5, ',');
    printf("Words from input5:\n");
    for (int i = 0; words5[i] != NULL; i++) {
        printf("%s\n", words5[i]);
    }
    printf("\n");

    // Free memory allocated for words
    free_array(words1, ft_count_words(input1, ' '));
    free_array(words2, ft_count_words(input2, ','));
    free_array(words3, ft_count_words(input3, ' '));
    free_array(words4, ft_count_words(input4, ' '));
    free_array(words5, ft_count_words(input5, ','));

    return 0;
}*/
