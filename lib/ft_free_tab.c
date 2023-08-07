#include "minilibft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_free_str(tab[i]);
	free(tab);
	tab = NULL;
}