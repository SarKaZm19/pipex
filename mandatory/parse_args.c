/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:12:33 by fvastena          #+#    #+#             */
/*   Updated: 2023/08/09 17:12:34 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_quote_trimmer(char **untrimmed)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (untrimmed[i])
	{
		if (untrimmed[i][0] == '\'' || untrimmed[i][0] == '\"')
		{
			tmp = ft_strtrim(untrimmed[i], "\"\'");
			if (!tmp)
				return (NULL);
			free(untrimmed[i]);
			untrimmed[i] = ft_strdup(tmp);
			free(tmp);
			if (!untrimmed[i])
				return (NULL);
		}
		i++;
	}
	return (untrimmed);
}

char	**ft_parse_arg(char *s)
{
	char	**parsed_cmd;

	parsed_cmd = ft_split_command(s, ' ');
	if (!parsed_cmd)
		return (NULL);
	parsed_cmd = ft_quote_trimmer(parsed_cmd);
	if (!parsed_cmd)
		return (NULL);
	return (parsed_cmd);
}
