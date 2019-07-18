/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llenotre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 22:08:23 by llenotre          #+#    #+#             */
/*   Updated: 2019/07/17 23:45:22 by llenotre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	backtrack(char **grid, size_t s, t_list *pieces, char c)
{
	t_pos pos;

	if (!pieces)
		return (0);
	ft_bzero(&pos, sizeof(t_pos));
	while (pos.y < s)
	{
		pos.x = 0;
		while (pos.x < s)
		{
			if (!can_place(grid, s, pieces->content, &pos))
			{
				place(grid, pieces->content, &pos, c);
				if (!backtrack(grid, s, pieces->next, c + 1))
					return (0);
				else
					place(grid, pieces->content, &pos, '.');
			}
			++pos.x;
		}
		++pos.y;
	}
	return (1);
}

static void	free_grid(char **grid, size_t s)
{
	size_t i;

	if (!grid)
		return ;
	i = 0;
	while (i < s)
	{
		free((void *)grid[i]);
		++i;
	}
	free((void *)grid);
}

static char	**alloc_grid(size_t s)
{
	char	**grid;
	size_t	i;

	if (!(grid = malloc(sizeof(char *) * s)))
		return (NULL);
	i = 0;
	while (i < s)
	{
		if (!(grid[i] = malloc(s)))
		{
			free_grid(grid, i);
			return (NULL);
		}
		ft_memset(grid[i], '.', s);
		++i;
	}
	return (grid);
}

static void	print_grid(char **grid, size_t s)
{
	size_t i;

	i = 0;
	while (i < s)
	{
		write(1, grid[i], s);
		write(1, "\n", 1);
		++i;
	}
}

int			solve(t_list *pieces)
{
	char	**grid;
	size_t	s;

	s = 2;
	while (1)
	{
		if (!(grid = alloc_grid(s)))
			return (1);
		if (!backtrack(grid, s, pieces, 'A'))
			break ;
		free_grid(grid, s);
		++s;
	}
	print_grid(grid, s);
	free_grid(grid, s);
	return (0);
}
