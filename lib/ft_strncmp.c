/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:49:15 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:49:16 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

static int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	while (n--)
	{
		if (*tmps1 != *tmps2)
			return (*tmps1 - *tmps2);
		tmps1++;
		tmps2++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len;

	len_s1 = ft_strlen(s1) + 1;
	len_s2 = ft_strlen(s2) + 1;
	len = len_s1;
	if (len_s1 > len_s2)
		len = len_s2;
	if (len > n)
		return (ft_memcmp(s1, s2, n));
	return (ft_memcmp(s1, s2, len));
}
