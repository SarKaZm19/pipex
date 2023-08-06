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

static void	close_files(t_data *datas)
{
	if (datas->infile != -1)
	{
		error_msg(close(datas->infile), "close: ");
		if (datas->here_doc == 1)
			error_msg(unlink(".heredoc_tmp"), "unlink: ");
		datas->infile = -1;
	}
	if (datas->outfile != -1)
	{
		close(datas->outfile);
		datas->outfile = -1;
	}
}

void	ft_free_datas(t_data *datas)
{
	close_files(datas);
	ft_free_tab(datas->args);
	ft_free_tab(datas->cmd);
	ft_free_str(datas->cmd_path);
	ft_free_tab(datas->env_paths);
	if (datas->pipe)
		free(datas->pipe);
}