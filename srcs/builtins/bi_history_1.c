/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 12:19:22 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 16:52:12 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "builtins.h"
#include "sh_termcaps.h"
#include "libft.h"

static void		ft_hist_help(void)
{
	ft_putstr("usage:\t[\033[1;37mhistory\033[0m]");
	ft_putendl("to display the last 20 commands");
	ft_putstr("\t[\033[1;37mhistory \033[1;32mNBR\033[0m]");
	ft_putendl("to display the last \033[1;32mNBR\033[0m commands");
	ft_putendl("\t[\033[1;37mhistory -c\033[0m] to clean history");
}

static void		ft_print_full_history(t_histo *histo, size_t nbr)
{
	t_llist			*llist;

	llist = histo->llist;
	if (nbr < histo->size)
	{
		while (llist->next != NULL && llist->position > histo->size - nbr + 1)
			llist = llist->next;
	}
	else
	{
		while (llist->next != NULL)
			llist = llist->next;
	}
	while (llist != NULL)
	{
		write(1, "\t", 1);
		ft_putnbr(llist->position);
		write(1, "  ", 2);
		ft_putendl(llist->line);
		llist = llist->prev;
	}
}

static void		ft_clean_history(int histo_fd)
{
	t_histo			*histo;

	histo = save_history(NULL, 0);
	if (histo_fd > 0)
	{
		close(histo_fd);
		unlink(histo->path_cmd);
	}
	if (histo != NULL)
	{
		free_histo();
		if (histo->path_cmd != NULL)
			free(histo->path_cmd);
		free(histo);
	}
	open_history();
}

int				bi_history(t_shell *shell)
{
	t_histo			*histo;
	int				nbr;

	histo = save_history(NULL, 0);
	if (shell->cmd[1] == NULL)
	{
		ft_print_full_history(histo, 20);
		return (0);
	}
	nbr = ft_atoi(shell->cmd[1]);
	if (ft_strcmp("-c", shell->cmd[1]) == 0)
		ft_clean_history(histo->fd);
	else if (nbr > 0)
		ft_print_full_history(histo, nbr);
	else
		ft_hist_help();
	return (0);
}
