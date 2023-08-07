#include "pipex_bonus.h"

static void	waitpid_handler(t_data *datas, int *exit_status)
{
	int		status;
	pid_t	w_pid;

	while (datas->nb_cmds > 0)
	{
		w_pid = waitpid(-1, &status, WNOHANG);
		if (w_pid == -1)
		{
			if(errno == EINTR)
				continue;
			else
				syscall_error(datas, w_pid, "waitpid: ");
		}
		else if (w_pid > 0)
		{
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			--datas->nb_cmds;
		}
	}
}

static char	**ft_quote_trimmer(char **untrimmed)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (untrimmed[i])
	{
		if (untrimmed[i][0] == '\'' || untrimmed[i][0] == '\"')
		{
			tmp = ft_strtrim(untrimmed[i], "\"\'");
			if (!tmp)
				return (NULL);
			free(untrimmed[i]);
			untrimmed[i] = ft_strdup(tmp);
			free(tmp);
			if (!untrimmed[i])
				return (NULL);
		}
		i++;
	}
	return (untrimmed);
}

static char	**ft_parse_arg(char *s)
{
	char	**parsed_cmd;

	parsed_cmd = ft_split_command(s, ' ');
	if (!parsed_cmd)
		return (NULL);
	parsed_cmd = ft_quote_trimmer(parsed_cmd);
	if (!parsed_cmd)
		return (NULL);
	return (parsed_cmd);
}

static void	ft_child_process(t_data *d, char **env)
{
	d->c_pid = fork();
	syscall_error(d, d->c_pid, "fork: ");
	if (!d->c_pid)
	{
		if ((d->cmd_i == 0 && d->infile != -1)
			|| ((d->cmd_i == d->nb_cmds - 1) && d->outfile != -1)
				|| ((d->cmd_i < d->nb_cmds - 1) && d->cmd_i > 0))
		{
			dup2_fill(d);
			ft_close_pipes(d);
			d->cmd = ft_parse_arg(d->args[d->cmd_i]);
			if (!d->cmd)
				syscall_error(d, -1, "malloc: ");
			d->cmd_path = get_cmd_path(d->cmd[0], d->env_paths);
			if (!d->cmd_path)
				cmd_error(d, d->cmd[0]);
			ft_free_child(d);
			syscall_error(d, execve(d->cmd_path, d->cmd, env), "execve: ");
		}
		ft_free_datas(d);
		exit(EXIT_FAILURE);
	}
}

void	ft_pipex(t_data *datas, char **env)
{
	int		exit_status;

	ft_create_pipes(datas);
	datas->child_pids = malloc(sizeof(pid_t) * datas->nb_cmds);
	if (!datas->child_pids)
		syscall_error(datas, -1, "malloc: ");
	datas->status = 0;
	while (++(datas->cmd_i) < datas->nb_cmds)
	{
		ft_child_process(datas, env);
		datas->child_pids[datas->cmd_i] = datas->c_pid;
	}
	ft_close_pipes(datas);
	waitpid_handler(datas, &exit_status);
	ft_free_datas(datas);
	if (exit_status != 0)
		exit(exit_status);
}
