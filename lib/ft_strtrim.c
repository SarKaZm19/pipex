/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:13:31 by fvastena          #+#    #+#             */
/*   Updated: 2023/08/09 17:13:32 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

static int	ft_check_set(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_trim_len(char *s1, const char *set, size_t *start)
{
	size_t	end;

	*start = 0;
	if (s1[0] == '\0')
		end = 0;
	else
		end = ft_strlen(s1) - 1;
	while (s1[*start] && ft_check_set(set, s1[*start]))
		*start += 1;
	if (s1[*start] == '\0')
		return (0);
	while (s1[end] && ft_check_set(set, s1[end]))
		end--;
	if (end == 0)
		return (0);
	return (end - (*start) + 1);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	char	*trimmed;
	char	*tmp;
	size_t	len_trim;
	size_t	start;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set || set[0] == '\0')
		return (ft_strdup(s1));
	tmp = (char *)s1;
	len_trim = ft_trim_len(tmp, set, &start);
	trimmed = malloc(sizeof(char) * (len_trim + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < len_trim)
	{
		trimmed[i] = tmp[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
