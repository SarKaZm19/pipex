/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:14:44 by fvastena          #+#    #+#             */
/*   Updated: 2023/08/09 17:14:44 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minilibft.h"
# ifndef USAGE_BONUS_ERROR
#  define USAGE_BONUS_ERROR "./pipex infile cmd1 cmd2 cmd3 [...] cmdn outfile\n\
	or\n./pipex here_doc LIMITER cmd1 cmd2 cmd3 [...] cmdn outfile\n"
# endif

typedef struct s_data
{
	int		nb_cmds;
	int		nb_pipes;
	int		here_doc;
	int		infile;
	int		outfile;
	int		cmd_i;
	int		c_pid;
	int		status;
	int		pipe_closed;
	int		*pipe;
	int		*pipe_status;
	pid_t	*child_pids;
	char	*cmd_path;
	char	**args;
	char	**cmd;
	char	**env_paths;
}				t_data;

//	PIPEX
// Core
void	ft_pipex(t_data *datas, char **env);

//	Struct
void	ft_init_datas(t_data *datas, int ac, char **av, char **env);

// PATHS
char	*get_cmd_path(char *cmd, char **paths);

// Pipes
void	ft_create_pipes(t_data *datas);
void	ft_close_pipes(t_data *datas);
void	dup2_fill(t_data *datas);

//	Errors
void	syscall_error(t_data *datas, int ret_value, char *msg);
void	cmd_error(t_data *datas, char *cmd);
void	error_msg(int ret_value, char *msg);

// Free
void	ft_free_datas(t_data *datas);

#endif
