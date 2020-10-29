/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 19:31:16 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 17:43:56 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

static void		backspace_middle(char **line, t_cursor *cursor)
{
	char			*tmp;
	char			*tmp2;
	char			*tmp3;

	tmp = ft_strsub(*line, 0, cursor->string - 1);
	tmp2 = ft_strsub(*line, (cursor->string), cursor->strlen);
	tmp3 = ft_strjoin(tmp, tmp2);
	ft_strcpy(*line, tmp3);
	key_is_left(line, cursor);
	tputs(tgetstr("cd", NULL), 1, tputs_putchar);
	ft_print_line(line, cursor);
	free(tmp);
	free(tmp2);
	free(tmp3);
}

int				key_is_backspace(char **line, t_cursor *cursor)
{
	if (cursor->string == 0)
		return (1);
	if (cursor->string == cursor->strlen)
	{
		(*line)[cursor->string - 1] = 0;
		key_is_left(line, cursor);
		tputs(tgetstr("cd", NULL), 1, tputs_putchar);
		cursor->strlen--;
	}
	else
		backspace_middle(line, cursor);
	return (0);
}

int				key_is_end(char **line, t_cursor *cursor)
{
	if (cursor->string < ft_strlen(*line))
	{
		while (key_is_right(line, cursor) != 1)
			;
	}
	return (0);
}

int				key_is_alt_plus_up(char **line, t_cursor *cursor)
{
	size_t			co;
	size_t			dest;

	co = tgetnum("co");
	if (cursor->string < co)
	{
		while (key_is_left(line, cursor) != 1)
			;
	}
	else
	{
		dest = cursor->string - co;
		while (cursor->string > dest)
			key_is_left(line, cursor);
	}
	return (0);
}

int				key_is_alt_plus_down(char **line, t_cursor *cursor)
{
	size_t			co;
	size_t			dest;

	co = tgetnum("co");
	if ((cursor->string + co) > cursor->strlen)
	{
		while (key_is_right(line, cursor) != 1)
			;
	}
	else
	{
		dest = cursor->string + co;
		while (cursor->string < dest)
			key_is_right(line, cursor);
	}
	return (0);
}
