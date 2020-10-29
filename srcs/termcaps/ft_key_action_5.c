/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 16:14:34 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 19:12:25 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

int				key_is_up(char **line, t_cursor *cursor)
{
	if (cursor->histo->llist == NULL || cursor->histo->llist->next == NULL)
		return (0);
	if (cursor->histo->position == 0)
		ft_strcpy(cursor->histo->current_cmd, *line);
	if (cursor->histo->position > 0)
		cursor->histo->llist = cursor->histo->llist->next;
	ft_memset(*line, '\0', BUFF_SIZE);
	cursor->histo->position++;
	ft_strcpy(*line, cursor->histo->llist->line);
	ft_print_line(line, cursor);
	while (key_is_right(line, cursor) != 1)
		;
	return (1);
}

int				key_is_down(char **line, t_cursor *cursor)
{
	if (cursor->histo->position == 0 || cursor->histo->llist == NULL)
		return (0);
	ft_memset(*line, '\0', BUFF_SIZE);
	if (cursor->histo->position > 1)
		cursor->histo->llist = cursor->histo->llist->prev;
	if (cursor->histo->position == 1)
		ft_strcpy(*line, cursor->histo->current_cmd);
	else
		ft_strcpy(*line, cursor->histo->llist->line);
	cursor->histo->position--;
	ft_print_line(line, cursor);
	while (key_is_right(line, cursor) != 1)
		;
	return (1);
}
