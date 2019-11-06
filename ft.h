/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalazar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 04:26:41 by asalazar          #+#    #+#             */
/*   Updated: 2019/08/20 18:37:07 by asalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_map_arg
{
	int			lines;
	int			columns;
	int			size;
	char		empty;
	char		obstacles;
	char		fill;
}				t_map_arg;

typedef struct	s_loc_map
{
	int			x;
	int			y;
	int			point;
}				t_loc_map;

char			*ft_read(int fd, t_map_arg *params);
int				**ft_cvmap(char *grid, t_map_arg *params);
char			*ft_strcpy(char *dest, char *src);
int				ft_atoi(char *str);
int				ft_strlen(char *str);
char			*ft_strncpy(char *dest, char *src, int n);
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_map_error();

#endif
