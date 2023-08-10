/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:04:26 by fvastena          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:27 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_close_files(t_data *datas)
{
	if (datas->infile != -1)
	{
		close(datas->infile);
		datas->infile = -1;
		if (datas->here_doc == 1 && datas->c_pid != 0)
			syscall_error(datas, unlink(".heredoc_tmp"), "unlink: ");
	}
	if (datas->outfile != -1)
	{
		close(datas->outfile);
		datas->outfile = -1;
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

void	ft_free_datas(t_data *datas)
{
	if (datas->c_pid != 0)
	{
		ft_free_tab(datas->cmd);
		ft_free_str(datas->cmd_path);
	}
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
	ft_free_tab(datas->env_paths);
	ft_free_pipes(datas);
	ft_close_files(datas);
}
