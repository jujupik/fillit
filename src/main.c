/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:19:42 by jrouchon          #+#    #+#             */
/*   Updated: 2019/07/17 22:11:51 by llenotre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	print_usage(void)
{
	ft_putendl("usage: fillit [file]");
}

static void	print_error(void)
{
	ft_putendl("error");
}

int			main(int argc, char **argv)
{
	t_list *pieces;

	pieces = NULL;
	if (argc != 2)
	{
		print_usage();
		return (1);
	}
	if (read_file(argv[1], &pieces) || check_pieces(pieces) || solve(pieces))
	{
		print_error();
		return (1);
	}
	ft_lstdel(&pieces, free_piece);
	return (0);
}
