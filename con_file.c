/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-thie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 00:01:45 by ple-thie          #+#    #+#             */
/*   Updated: 2019/08/20 16:58:16 by asalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

#define BUFF_SIZE 8192

int		**ft_cvmap(char *grid, t_map_arg *map)
{
	int		j;
	int		k;
	int		**data;

	j = -1;
	k = 0;
	if (!(data = (int**)malloc(sizeof(*data) * map->lines)) ||
		!(data[++j] = (int*)malloc(sizeof(**data) * map->columns)))
		return (0);
	while (*grid != '\0')
	{
		if (*grid == '\n')
		{
			if (((k != map->columns - 1)) ||
				!(data[++j] = (int*)malloc(sizeof(**data) * map->columns)))
				return (0);
			k = 0;
		}
		if (*grid == map->empty)
			data[j][k++] = -1;
		if (*grid++ == map->obstacles)
			data[j][k++] = 0;
	}
	return (j != map->lines - 1 ? 0 : data);
}

char	*ft_read_to(int fd, char c)
{
	char	*buff;
	char	*tmp;
	char	*input;
	int		len;

	if (!(buff = malloc(sizeof(*buff))))
		return (0);
	if (!(input = malloc(sizeof(*input))))
		return (0);
	input[0] = '\0';
	len = 0;
	while (read(fd, buff, 1) > 0 && *buff != c)
	{
		len++;
		tmp = input;
		if (!(input = malloc(sizeof(*input) * (++len + 1))))
			return (0);
		input[0] = '\0';
		ft_strcpy(input, tmp);
		ft_strncpy(input, buff, 1);
		free(tmp);
	}
	input[len] = '\0';
	return (input);
}

int		ft_utter_map(t_map_arg *map, char *params)
{
	int		i;
	int		len;
	char	*lines;

	len = 0;
	while (params[len] != '\0')
		len++;
	if (!(lines = (char*)malloc(sizeof(char) * (len - 3 + 1))))
		return (0);
	i = 0;
	while (params[i + 3] != '\0')
	{
		lines[i] = params[i];
		i++;
	}
	lines[i] = '\0';
	map->lines = ft_atoi(lines);
	map->empty = params[i++];
	map->obstacles = params[i++];
	map->fill = params[i];
	return (1);
}

char	*ft_read(int fd, t_map_arg *map)
{
	int		i;
	char	*tmp;
	char	*str;

	ft_utter_map(map, ft_read_to(fd, '\n'));
	tmp = ft_read_to(fd, '\n');
	map->columns = ft_strlen(tmp) + 1;
	if (map->lines <= 0)
		return (0);
	if (!(str = (char*)malloc(sizeof(*str) * (map->lines * map->columns))))
		return (0);
	str[0] = '\0';
	ft_strcpy(str, tmp);
	str[map->columns - 1] = '\n';
	str += map->columns;
	if ((i = read(fd, str, (map->lines - 1) * map->columns)) < 0)
		return (0);
	if (i != (map->lines - 1) * map->columns)
		return (0);
	str -= map->columns;
	if (read(fd, tmp, 1) > 0 || str[map->lines * map->columns - 1] != '\n')
		return (0);
	str[map->lines * map->columns - 1] = '\0';
	return (str);
}
