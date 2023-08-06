/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:49:36 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:49:37 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

static char	*ft_add_buf_to_line(char *line, char *buf, ssize_t len)
{
	ssize_t	line_len;
	char	*new_line;
	ssize_t	i;

	line_len = ft_strlen(line);
	if (!line_len && !len)
		return (NULL);
	new_line = malloc(sizeof(char) * (len + line_len + 1));
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < line_len)
		new_line[i] = line[i];
	while (i < line_len + len)
	{
		new_line[i++] = *buf;
		buf++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

static char	*ft_add_save_to_line(char *save)
{
	size_t	len_save;
	size_t	i;
	char	*line;

	len_save = ft_strlen(save);
	if (len_save == 0)
		return (NULL);
	line = malloc(sizeof(char) * (len_save + 1));
	if (!line)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len_save)
	{
		line[i] = save[i];
		save[i] = '\0';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read_loop(int fd, char *line)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	ret;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	ret = 1;
	while (ft_get_index(line, '\n') == -1 && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(line);
			return (NULL);
		}
		buf[ret] = '\0';
		line = ft_add_buf_to_line(line, buf, ret);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		nl_index;

	line = ft_add_save_to_line(save);
	nl_index = ft_get_index(line, '\n');
	if (nl_index == -1)
	{
		line = ft_read_loop(fd, line);
		if (!line)
			return (NULL);
		nl_index = ft_get_index(line, '\n');
		save[0] = '\0';
	}
	if (nl_index != -1)
	{
		ft_get_save(save, line, nl_index + 1);
		line = ft_get_ret_line(line, nl_index + 1);
	}
	return (line);
}
