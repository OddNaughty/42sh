/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 13:07:13 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 19:09:22 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

void			fill_histo_llist(t_histo *histo, char *line)
{
	t_llist			*new_cmd;
	static size_t	position = 0;

	if (line[0] == '\0')
		return ;
	if (histo->llist == NULL)
		position = 0;
	new_cmd = malloc(sizeof(t_llist));
	new_cmd->line = ft_strdup(line);
	new_cmd->position = position++;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	if (histo->llist == NULL)
		histo->llist = new_cmd;
	else
	{
		if (histo->initial != NULL)
			histo->llist = histo->initial;
		new_cmd->next = histo->llist;
		histo->llist->prev = new_cmd;
		histo->llist = new_cmd;
		histo->initial = new_cmd;
		histo->size++;
	}
}

t_llist			*free_llist(t_llist *llist)
{
	t_llist			*tmp;

	if (llist == NULL)
		return (NULL);
	else
	{
		tmp = llist->next;
		free(llist->line);
		free(llist);
		return (free_llist(tmp));
	}
}

void			free_histo(void)
{
	t_histo			*histo;

	histo = save_history(NULL, 0);
	free_llist(histo->llist);
}

t_histo			*save_history(t_histo *histo, int rw)
{
	static t_histo	*histo_save = NULL;

	if (rw == 1)
		histo_save = histo;
	return (histo_save);
}
