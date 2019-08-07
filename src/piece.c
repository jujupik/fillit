/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:29:05 by jrouchon          #+#    #+#             */
/*   Updated: 2019/08/07 19:29:11 by jrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	check(char *buff, size_t i)
{
	size_t count;

	count = 1;
	buff[i] = '.';
	if (i + 1 < 16 && buff[i + 1] == '#')
		count += check(buff, i + 1);
	if (i != 0 && buff[i - 1] == '#')
		count += check(buff, i - 1);
	if (i + 4 < 16 && buff[i + 4] == '#')
		count += check(buff, i + 4);
	if (i >= 4 && buff[i - 4] == '#')
		count += check(buff, i - 4);
	return (count);
}

static int	check_piece(char *buffer)
{
	char	*buff;
	size_t	i;
	int		r;

	if (!(buff = malloc(16)))
		return (1);
	ft_memcpy(buff, buffer, 16);
	i = 0;
	while (i < 16 && buffer[i] != '#')
		++i;
	r = check(buff, i);
	free((void *)buff);
	return (r == 4 ? 0 : 1);
}

static void	shift_piece(char *buffer)
{
	while (buffer[0] != '#' && buffer[1] != '#'
		&& buffer[2] != '#' && buffer[3] != '#')
	{
		ft_memmove(buffer, buffer + 4, 12);
		ft_memcpy(buffer + 12, "....", 4);
	}
	while (buffer[0] != '#' && buffer[4] != '#'
		&& buffer[8] != '#' && buffer[12] != '#')
	{
		ft_memmove(buffer, buffer + 1, 15);
		buffer[15] = '.';
	}
}

int			check_pieces(t_list *pieces)
{
	while (pieces)
	{
		if (check_piece(pieces->content))
			return (1);
		shift_piece(pieces->content);
		pieces = pieces->next;
	}
	return (0);
}

void		free_piece(void *content, size_t content_size)
{
	free((void *)content);
	(void)content_size;
}
