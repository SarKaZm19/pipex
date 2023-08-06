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

static void	ft_free_cmd(char **cmd)
{
	int	i;

	i = -1;
	if (cmd)
	{
		while (cmd[++i])
			cmd[i] = ft_free_str(cmd[i]);
		free(cmd);
		cmd = NULL;
	}
}

static void	ft_close_files(int outfile, int infile)
{
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
	size_t	i;

	ft_close_files(datas->infile, datas->outfile);
	ft_free_str(datas->path_cmd1);
	ft_free_str(datas->path_cmd2);
	ft_free_cmd(datas->cmd1);
	ft_free_cmd(datas->cmd2);
	i = -1;
	if (datas->paths)
	{
		while (datas->paths[++i])
			datas->paths[i] = ft_free_str(datas->paths[i]);
		free(datas->paths);
		datas->paths = NULL;
	}
}
