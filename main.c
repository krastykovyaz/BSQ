/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-thie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 23:47:59 by ple-thie          #+#    #+#             */
/*   Updated: 2019/08/21 19:23:47 by asalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int g_i = 0;

int		ft_calc_pos(int **map, int row, int col)
{
	int min;

	if (row == 0 || col == 0)
		return (1);
	min = map[row - 1][col];
	if (map[row][col - 1] < min)
		min = map[row][col - 1];
	if (map[row - 1][col - 1] < min)
		min = map[row - 1][col - 1];
	return (min + 1);
}

void	ft_sq_pos(int **map, t_loc_map *bestl)
{
	int i;
	int j;

	i = bestl->y;
	while (i > bestl->y - bestl->point)
	{
		j = bestl->x;
		while (j > bestl->x - bestl->point)
		{
			map[i][j] = -1;
			j--;
		}
		i--;
	}
}

int		**ft_calc_sq(int **map, t_map_arg map_arg)
{
	int			i;
	int			j;
	t_loc_map	bestl;

	bestl.point = -1;
	i = -1;
	while (++i < map_arg.lines)
	{
		j = -1;
		while (++j < map_arg.columns - 1)
		{
			if (map[i][j] == -1)
			{
				map[i][j] = ft_calc_pos(map, i, j);
				if (map[i][j] > bestl.point)
				{
					bestl.x = j;
					bestl.y = i;
					bestl.point = map[i][j];
				}
			}
		}
	}
	ft_sq_pos(map, &bestl);
	return (map);
}

void	ft_mapping(int **map, t_map_arg *params)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = -1;
	if (!(str = malloc(sizeof(*str) * params->columns)))
		return ;
	while (++i < params->lines)
	{
		k = 0;
		j = -1;
		while (++j < params->columns - 1)
		{
			if (map[i][j] == -1)
				str[k++] = params->fill;
			else if (map[i][j] == 0)
				str[k++] = params->obstacles;
			else
				str[k++] = params->empty;
		}
		str[k++] = '\n';
		str[k] = '\0';
		ft_putstr(str);
	}
}

int		main(int ac, char **av)
{
	int				fd;
	int				**map;
	char			*grid;
	t_map_arg		params;

	while (g_i++ < ac || (ac == 1 && g_i == 0))
	{
		if (ac == 1)
			fd = 0;
		else if ((fd = open(av[g_i], O_RDONLY)) == -1 && g_i < ac)
			ft_map_error();
		if (fd != -1)
		{
			if ((grid = ft_read(fd, &params))
				&& (map = ft_cvmap(grid, &params)))
			{
				ft_mapping(ft_calc_sq(map, params), &params);
				if (g_i + 1 < ac)
					ft_putchar('\n');
			}
			else
				ft_map_error();
		}
	}
	return (0);
}
