/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:18:49 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/30 17:18:50 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_close_fds(int outfile, int infile, int *pipe, int *pipe_status)
{
	if (pipe_status[0] != -1)
	{
		close(pipe[0]);
		pipe[0] = -1;
	}
	if (pipe_status[1] != -1)
	{
		close(pipe[1]);
		pipe[1] = -1;
	}
	if (infile != -1)
	{
		close(infile);
		infile = -1;
	}
	if (outfile != -1)
	{
		close(outfile);
		outfile = -1;
	}
}

void	ft_free_datas(t_data *datas)
{
	ft_free_tab(datas->paths);
	ft_free_str(datas->path_cmd1);
	ft_free_str(datas->path_cmd2);
	ft_free_tab(datas->cmd1);
	ft_free_tab(datas->cmd2);
	ft_close_fds(datas->infile, datas->outfile, datas->pipe_fd,
		datas->pipe_status);
}
