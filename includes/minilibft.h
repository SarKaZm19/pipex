/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:49:51 by fvastena          #+#    #+#             */
/*   Updated: 2023/07/24 19:49:52 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBFT_H
# define MINILIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

// GNL
char	*get_next_line(int fd);
ssize_t	ft_get_index(char *str, int c);
void	ft_get_save(char *save, char *line, size_t start);
char	*ft_get_ret_line(char *line, size_t nl_index);

// Vanilla
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);

// Added
void	ft_free_str(char *str);
void	ft_free_tab(char **tab);
char	**ft_split(char const *s, char c);
char	**ft_split_command(char const *s, char c);
char	*ft_strndup(char *str, size_t len);
char	*ft_strtrim(const char *s1, char const *set);

#endif
