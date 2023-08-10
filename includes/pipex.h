/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:23:04 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:23:05 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minilibft.h"
# ifndef USAGE_ERROR
#  define USAGE_ERROR "-pipex: usage: ./pipex infile cmd1 cmd2 outfile\n"
# endif

typedef struct s_data
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	int		pipe_status[2];
	int		cmd1_status;
	int		cmd2_status;
	int		cpid_1;
	int		cpid_2;
	char	*infile_name;
	char	*outfile_name;
	char	*path_cmd1;
	char	*path_cmd2;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
}				t_data;

// Core
int		ft_pipex(t_data *datas, char **env);
char	**ft_parse_arg(char *s);

// Paths
char	**get_paths(t_data *datas, char **env);
char	*get_cmd_path(char *cmd, char **paths);

// Errors
void	syscall_error(t_data *datas, int ret_value, char *msg);
void	cmd_error(t_data *datas, char *cmd);

// Free
void	ft_free_datas(t_data *datas);

#endif
