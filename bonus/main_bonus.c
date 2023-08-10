/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:04:38 by fvastena          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:39 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_struct(t_data *datas)
{
	datas->nb_cmds = 0;
	datas->nb_pipes = 0;
	datas->here_doc = 0;
	datas->infile = -1;
	datas->outfile = -1;
	datas->cmd_i = -1;
	datas->c_pid = -1;
	datas->status = 0;
	datas->pipe_closed = -1;
	datas->pipe = NULL;
	datas->pipe_status = NULL;
	datas->child_pids = NULL;
	datas->cmd_path = NULL;
	datas->args = NULL;
	datas->cmd = NULL;
	datas->env_paths = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	datas;

	if (ac >= 6)
	{
		ft_init_struct(&datas);
		ft_init_datas(&datas, ac, av, env);
		ft_pipex(&datas, env);
	}
	else
	{
		write (2, USAGE_BONUS_ERROR, ft_strlen(USAGE_BONUS_ERROR));
		return (1);
	}
	return (0);
}
