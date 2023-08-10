/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:47:51 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:47:52 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

static size_t	ft_partlen(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**ft_get_strs_tab(char **tab, char *tmp, size_t nb_parts, char c)
{
	size_t	i;
	size_t	part_len;
	size_t	j;

	i = 0;
	j = 0;
	while (j < nb_parts)
	{
		while (tmp[i] == c)
			i++;
		part_len = ft_partlen(tmp + i, c);
		tab[j] = ft_strndup(tmp + i, part_len);
		if (!tab[j])
			return (ft_free_tab(tab), NULL);
		i += part_len;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

static size_t	ft_word_count(char *str, char c)
{
	size_t	i;
	size_t	nb_word;

	i = 0;
	nb_word = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			nb_word++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (nb_word);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*tmp;
	size_t	nb_parts;

	if (!s)
		return (NULL);
	tmp = (char *)s;
	nb_parts = ft_word_count(tmp, c);
	strs = malloc(sizeof(char *) * (nb_parts + 1));
	if (!strs)
		return (NULL);
	return (ft_get_strs_tab(strs, tmp, nb_parts, c));
}
