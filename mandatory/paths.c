/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:30:19 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/22 18:30:20 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*path_in_cmd(char *cmd)
{
	if (access(cmd, X_OK) != 0)
		return (NULL);
	return (ft_strdup(cmd));
}

static char	*get_full_cmd(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*path_to_check;

	if (!paths || !paths[0])
		return(path_in_cmd(cmd));
	else
	{
		i = -1;
		while (paths[++i])
		{
			tmp = ft_strjoin(paths[i], "/");
			path_to_check = ft_strjoin(tmp, cmd);
			if (!tmp || !path_to_check)
				return (NULL);				
			free(tmp);
			if (access(path_to_check, X_OK) == 0)
				return (path_to_check);
			ft_free_str(path_to_check);
		}
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*path;

	path = NULL;
	if (cmd && ft_strchr(cmd, '/'))
		return (path_in_cmd(cmd));
	else if (cmd)
	{
		path = get_full_cmd(cmd, paths);
		if (path)
			return (path);
	}
	return (NULL);
}

char	**get_paths(t_data *datas, char **env)
{
	size_t	i;
	char	**paths;

	if (!env || !env[0])
		return (NULL);
	i = -1;
	paths = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			if (ft_strlen(env[i]) == 5)
				return (NULL);
			paths = ft_split(env[i] + 5, ':');
			if (paths == NULL)
				syscall_error(datas, -1, "malloc: ");
			return (paths);
		}
	}
	return (NULL);
}
