#include "minilibft.h"

static size_t	ft_skip_quotes(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	else if ((str[i] == '\"'))
	{
		i++;
		while (str[i] != '\"')
			i++;
	}
	return (i);
}

static size_t	ft_partlen(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i += ft_skip_quotes(str);
		i++;
	}
	return (i);
}

static char	**ft_get_strs_tab(char **strs, char *tmp, size_t nb_parts, char c)
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
		strs[j] = ft_strndup(tmp + i, part_len);
		if (!strs[j])
			return (ft_free_tab(strs), NULL);
		i += part_len;
		j++;
	}
	strs[j] = '\0';
	return (strs);
}

char	**ft_split_command(char const *s, char c)
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
		i += ft_skip_quotes(tmp + i);
		while (tmp[i] && tmp[i] != c)
			i++;
	}
	tab = malloc(sizeof(char *) * (nb_parts + 1));
	if (!tab)
		return (NULL);
	return(ft_get_strs_tab(tab, tmp, nb_parts, c));
}
