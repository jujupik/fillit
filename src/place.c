/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llenotre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:40:44 by llenotre          #+#    #+#             */
/*   Updated: 2019/07/17 23:41:07 by llenotre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		can_place(char **grid, size_t s, char *piece, t_pos *pos)
{
	t_pos p;

	ft_bzero(&p, sizeof(t_pos));
	while (p.x < 4 && p.y < 4)
	{
		if (piece[p.y * 4 + p.x] == '#'
			&& (pos->y + p.y >= s || pos->x + p.x >= s
				|| grid[pos->y + p.y][pos->x + p.x] != '.'))
			return (1);
		++p.x;
		if (p.x >= 4)
		{
			p.x = 0;
			++p.y;
		}
	}
	return (0);
}

void	place(char **grid, char *piece, t_pos *pos, char c)
{
	t_pos p;

	ft_bzero(&p, sizeof(t_pos));
	while (p.x < 4 && p.y < 4)
	{
		if (piece[p.y * 4 + p.x] == '#')
			grid[pos->y + p.y][pos->x + p.x] = c;
		++p.x;
		if (p.x >= 4)
		{
			p.x = 0;
			++p.y;
		}
	}
}
