/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:22:30 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/24 15:22:31 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				ft_putstr_fd(char *s, int fd);
int				    get_next_line(int fd, char **line);
char				*ft_strchr(const char *s, int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
char				**ft_split_str(char const *s, const char *del);
char			    *ft_strjoin_for_gnl(char *s1, char *s2);                
#endif
