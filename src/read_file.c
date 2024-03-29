/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:24:36 by jrouchon          #+#    #+#             */
/*   Updated: 2019/08/08 18:04:51 by jrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	*alloc_p(char *buffer)
{
	char	*buff;
	size_t	i;
	size_t	j;

	if (!(buff = malloc(16)))
		return (NULL);
	i = 0;
	j = 0;
	while (j < 20)
	{
		ft_memcpy(buff + i, buffer + j, 4);
		i += 4;
		j += 5;
	}
	return (buff);
}

static int	push_p(t_list **pieces, char *buffer)
{
	t_list	*p;
	t_list	*tmp;

	if (!buffer || !(p = ft_lstnew(buffer, 16)))
		return (1);
	if (*pieces)
	{
		tmp = *pieces;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = p;
	}
	else
		*pieces = p;
	return (0);
}

static int	check_p(char *buffer)
{
	int	side;
	int	i;

	side = 0;
	i = 0;
	while (i < 20)
	{
		if (buffer[i] == '#')
		{
			if ((i + 1) < 20 && buffer[i + 1] == '#')
				++side;
			if ((i - 1) >= 0 && buffer[i - 1] == '#')
				++side;
			if ((i + 5) < 20 && buffer[i + 5] == '#')
				++side;
			if ((i - 5) >= 0 && buffer[i - 5] == '#')
				++side;
		}
		++i;
	}
	if (side == 6 || side == 8)
		return (0);
	return (1);
}

static int	handle_piece(t_list **pieces, char *buffer)
{
	size_t	i;
	size_t	sharps;

	i = 0;
	sharps = 0;
	while (i < 20)
	{
		if ((i + 1) % 5 == 0)
		{
			if (buffer[i] != '\n')
				return (1);
		}
		else
		{
			if (buffer[i] == '#')
				++sharps;
			else if (buffer[i] != '.')
				return (1);
		}
		++i;
	}
	if (sharps != 4 || check_p(buffer) || push_p(pieces, alloc_p(buffer)))
		return (1);
	return (0);
}

int			read_file(char *file, t_list **pieces)
{
	int		fd;
	char	buffer[20];
	ssize_t	l;
	int		end;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (1);
	end = 0;
	while ((l = read(fd, buffer, sizeof(buffer))) > 0)
	{
		end = 0;
		if (l != sizeof(buffer))
			return (1);
		if (handle_piece(pieces, buffer))
			return (1);
		if (read(fd, buffer, 1) == 1 && buffer[0] == '\n')
			end = 1;
	}
	close(fd);
	if (!*pieces || end || l < 0)
		return (1);
	return (0);
}
