/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 12:51:46 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/26 14:57:15 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

void			ft_putchar_cursor(char **line, char ca, t_cursor *c)
{
	if (c->strlen < BUFF_SIZE)
	{
		write(1, &ca, 1);
		c->string++;
		c->strlen++;
	}
	if (is_right(c) == 1 && c->string == c->strlen)
	{
		ft_putchar(' ');
		ft_putstr("\033[1D");
	}
	*line = *line;
}

void			ft_putstr_cursor(char **line, char *str, t_cursor *c)
{
	while (*str)
	{
		ft_putchar_cursor(line, *str, c);
		str++;
	}
}

void			ft_print_line(char **line, t_cursor *cursor)
{
	size_t			cursor_save;

	cursor_save = cursor->string;
	while (key_is_left(line, cursor) != 1)
		;
	cursor->strlen = 0;
	tputs(tgetstr("cd", NULL), 1, tputs_putchar);
	ft_putstr_cursor(line, *line, cursor);
	while (cursor->string > cursor_save)
		key_is_left(line, cursor);
}

void			print_half_line(char *tm, t_cursor *cursor)
{
	size_t			index;

	index = 0;
	while (tm[index])
	{
		write(1, &tm[index], 1);
		index++;
		cursor->string++;
		if (is_right(cursor) == 1 && cursor->string == cursor->strlen)
		{
			ft_putchar(' ');
			ft_putstr("\033[1D");
		}
	}
}

void			insert_char(char **line, char c, t_cursor *cursor)
{
	size_t			index;
	size_t			index2;
	char			*tmp;
	size_t			cursor_save;

	index = 0;
	index2 = cursor->string + 1;
	cursor_save = cursor->string;
	tmp = ft_strsub(*line, cursor->string, cursor->strlen);
	(*line)[cursor->string] = c;
	while (tmp[index])
	{
		(*line)[index2] = tmp[index];
		index++;
		index2++;
	}
	cursor->strlen++;
	ft_putchar(c);
	cursor->string++;
	print_half_line(tmp, cursor);
	while (cursor->string != cursor_save && key_is_left(line, cursor) != 1)
		;
	key_is_right(line, cursor);
	free(tmp);
}
