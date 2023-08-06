/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:49:46 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:49:47 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

ssize_t	ft_get_index(char *str, int c)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_get_save(char *save, char *line, size_t start)
{
	size_t	i;

	i = 0;
	while (line[start])
	{
		save[i] = line[start];
		i++;
		start++;
	}
	save[i] = '\0';
}

char	*ft_get_ret_line(char *line, size_t nl_index)
{
	size_t	i;
	char	*new_line;

	new_line = malloc(sizeof(char) * (nl_index + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < nl_index)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}
