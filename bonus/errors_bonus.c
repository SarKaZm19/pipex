#include "pipex_bonus.h"

void	error_msg(int ret_value, char *msg)
{
	if (ret_value == -1)
	{
		write(2, "pipex: ", 8);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
}

void	cmd_error(t_data *datas, char *cmd)
{
	write(2, "pipex: ", 8);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	ft_free_datas(datas);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(EXIT_FAILURE);
}

void	syscall_error(t_data *datas, int ret_value, char *msg)
{
	if (ret_value == -1)
	{
		write(2, "pipex: ", 8);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		ft_free_datas(datas);
		exit(EXIT_FAILURE);
	}
}