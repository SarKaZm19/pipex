/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:48:51 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:48:52 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = 0;
	while (tmp[i] != (char)c)
	{
		if (tmp[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)tmp + i);
}
