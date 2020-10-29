/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 12:05:57 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/26 14:59:28 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

int				key_is_home(char **line, t_cursor *cursor)
{
	if (cursor->string > 0)
	{
		while (key_is_left(line, cursor) != 1)
			;
	}
	return (0);
	*line = *line;
}

int				is_left(t_cursor *cursor)
{
	int				co;

	co = tgetnum("co");
	if (((cursor->string + cursor->lprompt) % co) == 0)
		return (1);
	else if ((cursor->string + cursor->lprompt) % co == 1)
		return (2);
	else
		return (0);
}

int				key_is_left(char **line, t_cursor *cursor)
{
	if (cursor->string == 0)
		return (1);
	tputs(tgetstr("le", NULL), 1, tputs_putchar);
	cursor->string--;
	return (0);
	ft_strlen(*line);
}

int				is_right(t_cursor *cursor)
{
	int				co;

	co = tgetnum("co");
	if (((cursor->string + cursor->lprompt) % co) == 0)
		return (1);
	if (((cursor->string + 1 + cursor->lprompt) % co) == 0)
		return (2);
	else
		return (0);
}

int				key_is_right(char **line, t_cursor *cursor)
{
	if (cursor->string == cursor->strlen)
		return (1);
	if (is_right(cursor) == 2)
		ft_putstr("\033[1B\033[2000D");
	else
		tputs(tgetstr("nd", NULL), 1, tputs_putchar);
	cursor->string++;
	return (0);
	*line = *line;
}
