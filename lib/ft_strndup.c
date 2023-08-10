/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:13:25 by fvastena          #+#    #+#             */
/*   Updated: 2023/08/09 17:13:26 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_strndup(char *str, size_t len)
{
	size_t	i;
	char	*dup;

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < len && str[i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}
