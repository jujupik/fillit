/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:24:36 by jrouchon          #+#    #+#             */
/*   Updated: 2019/07/17 23:43:15 by llenotre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	*alloc_piece(char *buffer)
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

static int	push_piece(t_list **pieces, char *buffer)
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
	if (sharps != 4 || push_piece(pieces, alloc_piece(buffer)))
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
