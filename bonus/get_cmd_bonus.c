#include "pipex_bonus.h"

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
