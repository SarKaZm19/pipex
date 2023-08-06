#include "pipex_bonus.h"

static char	**get_paths(t_data *datas, char **env)
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

static void	get_args(t_data *datas,char **av)
{
	int	i;

	datas->args = malloc(sizeof(char*) * (datas->nb_cmds + 1));
	if (!datas->args)
		syscall_error(datas, -1, "malloc: ");
	i = -1;
	while (++i < datas->nb_cmds)
	{
		datas->args[i] = ft_strdup(av[i]);
		if (datas->args[i] == NULL)
			syscall_error(datas, -1, "malloc: ");
	}
	datas->args[datas->nb_cmds] = NULL;
}

void	here_doc_gnl(t_data *datas, char *delimiter)
{
	char	*new_line;

	new_line = NULL;
	datas->infile = open(".heredoc_tmp"
		, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	error_msg(datas->infile, "here_doc: ");
	if (datas->infile == -1)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (new_line)
			free(new_line);
		new_line = get_next_line(0);
		if (!new_line)
			syscall_error(datas, -1, "GNL: ");
		if (!ft_strncmp(new_line, delimiter, ft_strlen(delimiter)))
			break;
		else
			syscall_error(datas, write(datas->infile, new_line
				, ft_strlen(new_line)), "write: ");
	}
	ft_free_str(new_line);
	syscall_error(datas, close(datas->infile), "close: ");
}

void	here_doc(t_data *datas, int ac, char **av)
{
	here_doc_gnl(datas, av[2]);
	if (datas->infile != -1)
	{
		datas->infile = open(".heredoc_tmp", O_RDONLY | O_CLOEXEC);
		error_msg(datas->infile, "here_doc: ");
		if (datas->infile == -1)
			syscall_error(datas, unlink(".heredoc_tmp"), "unlink: ");
	}
	datas->outfile = open(av[ac - 1]
		, O_RDWR | O_APPEND | O_CLOEXEC | O_CREAT, 0644);
	error_msg(datas->outfile, av[ac - 1]);
	datas->here_doc = 1;
}

void	ft_init_datas(t_data *datas, int ac, char **av, char **env)
{
	datas->infile = -1;
	datas->outfile = -1;
	datas->args = NULL;
	datas->env_paths = NULL;
	datas->pipe = NULL;
	datas->cmd_path = NULL;
	datas->cmd = NULL;
	if (!ft_strncmp(av[1], "here_doc", 8))
		here_doc(datas, ac, av);
	else
	{
		datas->infile = open(av[1], O_RDONLY | O_CLOEXEC);
		error_msg(datas->infile, av[1]);
		datas->outfile = open(av[ac - 1]
			, O_WRONLY | O_TRUNC | O_CLOEXEC | O_CREAT, 0644);
		error_msg(datas->outfile, av[ac - 1]);
		datas->here_doc = 0;
	}
	datas->nb_cmds = ac - 3 - datas->here_doc;
	get_args(datas, av + 2 + datas->here_doc);
	datas->env_paths = get_paths(datas, env);
	datas->nb_pipes = 2 * (datas->nb_cmds - 1);
	datas->pipe = (int *)malloc(sizeof(int) * datas->nb_pipes);
	if (!datas->pipe)
		syscall_error(datas, -1, "malloc: ");
}
