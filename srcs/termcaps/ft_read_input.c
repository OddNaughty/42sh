/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 11:46:06 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 17:21:19 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"
#include "termcaps_tab.h"

static int		check_hints_2(char **line, t_cursor *cursor, size_t key)
{
	if (key == RETURN_KEY)
	{
		if (key_is_return(line, cursor) == 1)
			return (1);
	}
	if (key < 128 && key > 31 && (ft_strlen(*line) < BUFF_SIZE))
		key_is_print(line, cursor, key);
	if (key == 4 && (*line)[0] == '\0')
	{
		ft_putendl("exit: (ctrl + D)");
		exit(0);
	}
	return (0);
}

static int		check_hints(char **line, t_cursor *cursor, size_t key)
{
	extern t_funct	g_functab[CMD_NBR];
	int				i;

	i = 0;
	while (i < CMD_NBR)
	{
		if (key == g_functab[i].key_value)
			return (g_functab[i].process(line, cursor));
		i++;
	}
	return (-1);
}

static t_cursor	ft_fill_cursor(int len)
{
	t_cursor		cursor;
	t_histo			*history;

	history = save_history(NULL, 0);
	cursor.string = 0;
	cursor.quote = ft_strnew(6);
	cursor.strlen = 0;
	cursor.lprompt = len;
	cursor.histo = history;
	cursor.histo->current_cmd = ft_strnew(BUFF_SIZE);
	return (cursor);
}

static void		free_cursor(t_cursor *cursor)
{
	free(cursor->quote);
	free(cursor->histo->current_cmd);
	cursor->string = 0;
}

void			read_input(char **line, int len)
{
	char			buffer[5];
	t_cursor		cursor;

	save_line_ptr(&(*line), 1);
	save_cursor_ptr(&cursor, 1);
	cursor = ft_fill_cursor(len);
	while (1)
	{
		ft_bzero(buffer, 5);
		read(0, buffer, 5);
		if (check_hints(line, &cursor, *(unsigned int *)buffer) < 0)
		{
			if (check_hints_2(line, &cursor, *(unsigned int *)buffer) == 1)
			{
				free_cursor(&cursor);
				return ;
			}
			if (*(unsigned int *)buffer == 27)
			{
				free(cursor.quote);
				restore_shell();
				exit(1);
			}
		}
	}
}
