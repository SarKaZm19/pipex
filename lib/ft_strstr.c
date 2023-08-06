/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:49:20 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:49:21 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*hay;

	len2 = ft_strlen(little);
	if (!big)
		return (NULL);
	if (len2 == 0)
		return ((char *)big);
	hay = (char *)big;
	i = 0;
	while (hay[i] != '\0')
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		if (j == len2)
			return (hay + i);
		i++;
	}
	return (NULL);
}
