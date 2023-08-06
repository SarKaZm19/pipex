#include "pipex_bonus.h"

int	main (int ac, char **av, char **env)
{
	t_data	datas;

	if (ac >= 6)
	{
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
