#include "pipex_bonus.h"

void	dup2_fill(t_data *datas)
{
	if (datas->cmd_i == 0)
	{
		syscall_error(datas, dup2(datas->infile, 0), "dup2: ");
		syscall_error(datas, dup2(datas->pipe[1], 1), "dup2: ");
	}
	else if (datas->cmd_i == datas->nb_cmds - 1)
	{
		syscall_error(datas, dup2(datas->pipe[2 * datas->cmd_i - 2], 0)
			, "dup2: ");
		syscall_error(datas, dup2(datas->outfile, 1), "dup2: ");
	}
	else
	{
		syscall_error(datas, dup2(datas->pipe[2 * datas->cmd_i - 2], 0)
			, "dup2: ");
		syscall_error(datas, dup2(datas->pipe[2 * datas->cmd_i + 1], 1)
			, "dup2: ");
	}
}

void	ft_close_pipes(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_pipes)
	{
		if (datas->pipe_status[i] != -1)
		{
			close(datas->pipe[i]);
			datas->pipe_status[i] = -1;
		}
	}
	if (i == datas->nb_pipes)
		datas->pipe_closed = 0;
}

void	ft_create_pipes(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_cmds - 1)
	{
		syscall_error(datas, pipe(datas->pipe + 2 * i), "pipe: ");
		datas->pipe_status[i * 2] = 0;
		datas->pipe_status[i * 2 + 1] = 0;
	}
}
