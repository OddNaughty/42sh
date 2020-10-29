/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 13:44:28 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 18:30:40 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"

char			**save_line_ptr(char **line, int rw)
{
	static char		**line_ptr = NULL;

	if (rw == 1)
		line_ptr = line;
	return (line_ptr);
}

t_cursor		*save_cursor_ptr(t_cursor *cursor, int rw)
{
	static t_cursor	*cursor_ptr = NULL;

	if (rw == 1)
		cursor_ptr = cursor;
	return (cursor_ptr);
}
