/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:18:49 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/30 17:18:50 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_free_str(tab[i]);
	free(tab);
}

static void	ft_close_fds(int outfile, int infile, int *pipe, int *pipe_status)
{
	if (pipe_status[0] != -1)
	{
		error_msg(close(pipe[0]), "close a");
		pipe[0] = -1;
	}
	if (pipe_status[1] != -1)
	{
		error_msg(close(pipe[1]), "close b");
		pipe[1] = -1;
	}
	if (infile != -1)
	{
		error_msg(close(infile), "close c");
		infile = -1;
	}
	if (outfile != -1)
	{
		error_msg(close(outfile), "close d");
		outfile = -1;
	}
}

void	ft_free_datas(t_data *datas)
{
	ft_close_fds(datas->infile, datas->outfile, datas->pipe_fd, datas->pipe_status);
	ft_free_str(datas->path_cmd1);
	ft_free_str(datas->path_cmd2);
	ft_free_tab(datas->cmd1);
	ft_free_tab(datas->cmd2);
	ft_free_tab(datas->paths);
}
