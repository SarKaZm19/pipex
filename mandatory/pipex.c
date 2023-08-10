/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:30:22 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/22 18:30:23 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process1(t_data *datas, char **env)
{
	datas->infile = open(datas->infile_name, O_RDONLY | O_CLOEXEC);
	syscall_error(datas, datas->infile, datas->infile_name);
	syscall_error(datas, close(datas->pipe_fd[0]), "close: ");
	datas->pipe_status[0] = -1;
	syscall_error(datas, dup2(datas->pipe_fd[1], STDOUT_FILENO), "dup2: ");
	syscall_error(datas, close(datas->pipe_fd[1]), "close: ");
	datas->pipe_status[1] = -1;
	syscall_error(datas, dup2(datas->infile, STDIN_FILENO), "dup2 :");
	syscall_error(datas, close(datas->infile), "close: ");
	datas->infile = -1;
	datas->path_cmd1 = get_cmd_path(datas->cmd1[0], datas->paths);
	if (!datas->path_cmd1)
		cmd_error(datas, datas->cmd1[0]);
	ft_free_tab(datas->paths);
	syscall_error(datas, execve(datas->path_cmd1, datas->cmd1, env),
		"execve: ");
}

static void	child_process2(t_data *datas, char **env)
{
	datas->outfile = open(datas->outfile_name,
			O_WRONLY | O_TRUNC | O_CLOEXEC | O_CREAT, 0644);
	syscall_error(datas, datas->outfile, datas->outfile_name);
	syscall_error(datas, close(datas->pipe_fd[1]), "close: ");
	datas->pipe_status[1] = -1;
	syscall_error(datas, dup2(datas->pipe_fd[0], STDIN_FILENO), "dup2: ");
	syscall_error(datas, close(datas->pipe_fd[0]), "close: ");
	datas->pipe_status[0] = -1;
	syscall_error(datas, dup2(datas->outfile, STDOUT_FILENO), "dup2: ");
	syscall_error(datas, close(datas->outfile), "close: ");
	datas->outfile = -1;
	datas->path_cmd2 = get_cmd_path(datas->cmd2[0], datas->paths);
	if (!datas->path_cmd2)
		cmd_error(datas, datas->cmd2[0]);
	ft_free_tab(datas->paths);
	syscall_error(datas, execve(datas->path_cmd2, datas->cmd2, env),
		"execve: ");
}

static void	waitpid_handler(int cpid, int *status)
{
	int	waitpid_val;

	waitpid_val = waitpid(cpid, status, 0);
	while (waitpid_val == -1 && errno == EINTR)
		waitpid_val = waitpid(cpid, status, 0);
}

static void	parent_process(t_data *datas)
{
	syscall_error(datas, close(datas->pipe_fd[1]), "close: ");
	datas->pipe_status[1] = -1;
	syscall_error(datas, close(datas->pipe_fd[0]), "close: ");
	datas->pipe_status[0] = -1;
	waitpid_handler(datas->cpid_1, &datas->cmd1_status);
	waitpid_handler(datas->cpid_2, &datas->cmd2_status);
	if (WIFEXITED(datas->cmd2_status))
		datas->cmd2_status = WEXITSTATUS(datas->cmd2_status);
	ft_free_datas(datas);
	if (datas->cmd2_status != 0)
		exit(datas->cmd2_status);
}

int	ft_pipex(t_data *datas, char **env)
{
	datas->cpid_1 = fork();
	syscall_error(datas, datas->cpid_1, "fork: ");
	if (datas->cpid_1 == 0)
		child_process1(datas, env);
	else if (datas->cpid_1 > 0)
	{
		datas->cpid_2 = fork();
		syscall_error(datas, datas->cpid_2, "fork: ");
		if (datas->cpid_2 == 0)
			child_process2(datas, env);
		parent_process(datas);
	}
	return (0);
}
