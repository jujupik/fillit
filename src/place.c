/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:29:27 by jrouchon          #+#    #+#             */
/*   Updated: 2019/08/07 19:29:34 by jrouchon         ###   ########.fr       */
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
