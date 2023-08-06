#include "pipex_bonus.h"

static void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		ft_free_str(tab[i]);
	free(tab);
	tab = NULL;
}

static void	ft_close_files(t_data *datas)
{
	int	infile_close_val;
	int	outfile_close_val;

	if (datas->infile != -1)
	{
		infile_close_val = close(datas->infile);
		datas->infile = -1;
		syscall_error(datas, infile_close_val, "close: ");
		if (datas->here_doc == 1 && infile_close_val == 0 && datas->c_pid != 0)
			syscall_error(datas, unlink(".heredoc_tmp"), "unlink: ");
	}
	if (datas->outfile != -1)
	{
		outfile_close_val = close(datas->outfile);
		datas->outfile = -1;
		syscall_error(datas, outfile_close_val, "close: ");
	}
}

void	ft_free_pipes(t_data *datas)
{
	if (datas->pipe)
	{
		if (datas->pipe_status)
			ft_close_pipes(datas);
		if (datas->pipe_closed == 0)
		{
			free(datas->pipe_status);
			datas->pipe_status = NULL;
		}
		free(datas->pipe);
		datas->pipe = NULL;
	}
}

void	ft_free_child(t_data *datas)
{
	if (datas->pipe)
		free(datas->pipe);
	if (datas->pipe_closed)
		free(datas->pipe_status);
	if (datas->child_pids)
		free(datas->child_pids);
	ft_free_tab(datas->env_paths);
}

void	ft_free_datas(t_data *datas)
{
	ft_free_tab(datas->cmd);
	ft_free_str(datas->cmd_path);
	ft_free_tab(datas->env_paths);
	if (datas->args)
	{
		free(datas->args);
		datas->args = NULL;
	}
	if (datas->child_pids)
	{
		free(datas->child_pids);
		datas->child_pids = NULL;
	}
	ft_free_pipes(datas);
	if (datas->infile && datas->outfile)
		ft_close_files(datas);
}
