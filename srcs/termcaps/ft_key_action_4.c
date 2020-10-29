/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 17:53:04 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 14:33:03 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

int				key_is_ctrl_plus_l(char **line, t_cursor *cursor)
{
	size_t			cursor_save;

	cursor_save = cursor->string;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	ft_putuser();
	cursor->strlen = 0;
	cursor->string = 0;
	ft_putstr_cursor(line, *line, cursor);
	while (cursor->string > cursor_save)
		key_is_left(line, cursor);
	return (1);
}

int				key_is_return(char **line, t_cursor *cursor)
{
	int				i;

	i = 0;
	ft_putchar('\n');
	ft_bzero(cursor->quote, 6);
	search_quote((*line), cursor);
	while (i < 6)
	{
		if (cursor->quote[i] != 0)
		{
			ft_putstr("quote> ");
			return (0);
		}
		i++;
	}
	if ((*line)[0] != 0)
	{
		fill_histo_llist(cursor->histo, *line);
		if (cursor->histo->fd > 0)
			ft_putendl_fd(*line, cursor->histo->fd);
	}
	cursor->histo->position = 0;
	return (1);
}

static void		char_is_quote(char c, t_cursor *cursor)
{
	if (c == '\'' && cursor->quote[1] == 0 && cursor->quote[2] == 0)
		cursor->quote[0] = (cursor->quote[0] + 1) % 2;
	else if (c == '\"' && cursor->quote[0] == 0 && cursor->quote[2] == 0)
		cursor->quote[1] = (cursor->quote[1] + 1) % 2;
	else if (c == '`' && cursor->quote[0] == 0 && cursor->quote[1] == 0)
		cursor->quote[2] = (cursor->quote[2] + 1) % 2;
	else if (c == '(' && cursor->quote[0] == 0 && cursor->quote[1] == 0)
		cursor->quote[3] = cursor->quote[3] + 1;
	else if (c == ')' && cursor->quote[3] != 0 && cursor->quote[0] == 0
				&& cursor->quote[1] == 0 && cursor->quote[2] == 0)
		cursor->quote[3] = cursor->quote[3] - 1;
	else if (c == '[' && cursor->quote[0] == 0
				&& cursor->quote[1] == 0 && cursor->quote[2] == 0)
		cursor->quote[4] = cursor->quote[4] + 1;
	else if (c == ']' && cursor->quote[4] != 0 && cursor->quote[0] == 0
				&& cursor->quote[1] == 0 && cursor->quote[2] == 0)
		cursor->quote[4] = cursor->quote[4] - 1;
	else if (c == '{' && cursor->quote[0] == 0
				&& cursor->quote[1] == 0 && cursor->quote[2] == 0)
		cursor->quote[5] = cursor->quote[5] + 1;
	else if (c == '}' && cursor->quote[5] != 0 && cursor->quote[0] == 0
				&& cursor->quote[1] == 0 && cursor->quote[2] == 0)
		cursor->quote[5] = cursor->quote[5] - 1;
}

void			search_quote(char *s, t_cursor *cursor)
{
	size_t			i;

	i = 0;
	while (s[i])
	{
		char_is_quote(s[i], cursor);
		i++;
	}
}

int				key_is_del(char **line, t_cursor *cursor)
{
	char			*tmp;
	char			*tmp2;
	char			*tmp3;

	if (cursor->string != cursor->strlen)
	{
		if (cursor->string == 0)
		{
			tmp = ft_strsub(*line, 1, cursor->strlen);
			ft_strcpy(*line, tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_strsub(*line, 0, cursor->string);
			tmp2 = ft_strsub(*line, (cursor->string + 1), cursor->strlen);
			tmp3 = ft_strjoin(tmp, tmp2);
			ft_strcpy(*line, tmp3);
			free(tmp);
			free(tmp2);
			free(tmp3);
		}
		ft_print_line(line, cursor);
	}
	return (0);
}
