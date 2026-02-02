/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 07:48:05 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 07:48:08 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_content(const char *content)
{
	int		i;

	if (!content || content[0] == '\0' || content[0] == '\n')
		return (0);
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n' && content[i + 1] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_map_lines(char **map, int *height)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
			return (0);
		i++;
	}
	*height = i;
	return (1);
}

char	**split_map(const char *content, int *height)
{
	char	**map;

	if (!validate_content(content))
		return (NULL);
	map = ft_split(content, '\n');
	if (!map)
		return (NULL);
	if (!validate_map_lines(map, height))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
