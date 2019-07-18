/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:24:45 by jrouchon          #+#    #+#             */
/*   Updated: 2019/07/17 23:42:38 by llenotre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include "../libft/libft.h"

typedef struct	s_pos
{
	size_t x;
	size_t y;
}				t_pos;

int				read_file(char *file, t_list **pieces);

int				check_pieces(t_list *pieces);
void			free_piece(void *content, size_t content_size);

int				solve(t_list *pieces);

int				can_place(char **grid, size_t s, char *piece, t_pos *pos);
void			place(char **grid, char *piece, t_pos *pos, char c);

#endif
