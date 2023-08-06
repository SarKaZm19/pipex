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

static char	**ft_free_return(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

static size_t	ft_partlen(char *tmp, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (tmp[i] == c)
		i++;
	while (tmp[i])
	{
		i++;
		count++;
		if (tmp[i] == c)
			return (count);
	}
	return (count);
}

static char	*ft_splitdup(char *str, size_t len)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**ft_get_strs_tab(char **tab, char *tmp, size_t nb_parts, char c)
{
	size_t	i;
	size_t	part_len;
	size_t	j;

	i = 0;
	j = 0;
	while (j < nb_parts && tmp[i])
	{
		while (tmp[i] == c)
			i++;
		part_len = ft_partlen(tmp + i, c);
		tab[j] = ft_splitdup(tmp + i, part_len);
		if (!tab[j])
			return (ft_free_return(tab));
		i = i + part_len;
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*tmp;
	size_t	nb_parts;
	size_t	i;

	if (!s)
		return (NULL);
	tmp = (char *)s;
	i = 0;
	nb_parts = 0;
	while (tmp[i] != '\0')
	{
		while (tmp[i] != '\0' && tmp[i] == c)
			i++;
		if (tmp[i] && tmp[i] != c)
			nb_parts++;
		while (tmp[i] && tmp[i] != c)
			i++;
	}
	tab = malloc(sizeof(char *) * (nb_parts + 1));
	if (!tab)
		return (NULL);
	tab = ft_get_strs_tab(tab, tmp, nb_parts, c);
	return (tab);
}
