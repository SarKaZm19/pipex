/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:30:15 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/22 18:30:16 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipe_status(t_data *datas)
{
	datas->pipe_status[0] = -1;
	datas->pipe_status[1] = -1;
	syscall_error(datas, pipe(datas->pipe_fd), "pipe: ");
	datas->pipe_status[0] = 0;
	datas->pipe_status[1] = 0;
}

static void	init_datas(t_data *datas, char **av, char **env)
{
	datas->infile_name = av[1];
	datas->outfile_name = av[4];
	datas->infile = -1;
	datas->outfile = -1;
	datas->cmd1 = ft_parse_arg(av[2]);
	datas->cmd2 = ft_parse_arg(av[3]);
	if (!datas->cmd1 || !datas->cmd2)
		syscall_error(datas, -1, "malloc: ");
	datas->paths = get_paths(datas, env);
	datas->cmd1_status = 0;
	datas->cmd2_status = 0;
	datas->path_cmd1 = NULL;
	datas->path_cmd2 = NULL;
	pipe_status(datas);
}

int	main(int ac, char **av, char **env)
{
	t_data	datas;

	if (ac == 5)
	{
		init_datas(&datas, av, env);
		ft_pipex(&datas, env);
	}
	else
	{
		write(2, USAGE_ERROR, ft_strlen(USAGE_ERROR));
		return (1);
	}
	return (0);
}
