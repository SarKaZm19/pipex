#include "pipex_bonus.h"

static void	waitpid_handler(t_data *datas, int *exit_status)
{
	int		status;
	pid_t	w_pid;

	while (datas->nb_cmds > 0)
	{
		w_pid = waitpid(-1, &status, 0);
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

static void	ft_child_process(t_data *d, char **env)
{
	d->c_pid = fork();
	syscall_error(d, d->c_pid, "fork: ");
	if (!d->c_pid)
	{
		if ((d->cmd_i == 0 && d->infile != -1) || (d->cmd_i == d->nb_cmds - 1
			&& d->outfile != -1) || (d->cmd_i > 0 && d->cmd_i < d->nb_cmds - 1))
		{
			dup2_fill(d);
			ft_close_pipes(d);
			d->cmd = ft_split(d->args[d->cmd_i], ' ');
			if (!d->cmd)
				syscall_error(d, -1, "malloc: ");
			d->cmd_path = get_cmd_path(d->cmd[0], d->env_paths);
			if (!d->cmd_path)
				cmd_error(d, d->cmd[0]);
			syscall_error(d, execve(d->cmd_path, d->cmd, env), "execve: ");
		}
		exit(EXIT_FAILURE);
	}
}

void	ft_pipex(t_data *datas, char **env)
{
	pid_t	*child_pids;
	int		i;
	int		exit_status;

	child_pids = malloc(sizeof(pid_t) * datas->nb_cmds);
	if (!child_pids)
		syscall_error(datas, -1, "malloc: ");
	i = -1;
	datas->status = 0;
	ft_create_pipes(datas);
	while (++i < datas->nb_cmds)
	{
		datas->cmd_i = i;
		ft_child_process(datas, env);
		child_pids[i] = datas->c_pid;
	}
	ft_close_pipes(datas);
	waitpid_handler(datas, &exit_status);
	free(child_pids);
	ft_free_datas(datas);
	if (exit_status != 0)
		exit(exit_status);
}
