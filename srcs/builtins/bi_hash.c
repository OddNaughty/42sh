/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elazarov <elazarov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 22:34:04 by elazarov          #+#    #+#             */
/*   Updated: 2014/03/27 16:20:31 by elazarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "sh_termcaps.h"

static void hash_display(t_shell *shell, int fg)
{
	t_hlist *ptr;

	if (fg == 1)
		write(1, "hits\tcommand\n", 13);
	ptr = shell->hlist;
	while (ptr)
	{
		if (fg == 1)
		{
			if (ptr->count < 1000)
				write(1, " ", 1);
			if (ptr->count < 100)
				write(1, " ", 1);
			if (ptr->count < 10)
				write(1, " ", 1);
			ft_putnbr(ptr->count);
			write(1, "\t", 1);
		}
		if (fg == 1 || (write(1, "builtin hash -p ", 16)))
			ft_putstr(shell->htab[ptr->code]);
		if (fg == 0 && write(1, " ", 1))
			ft_putstr((ft_strrchr(shell->htab[ptr->code], '/') + 1));
		ft_putchar('\n');
		ptr = ptr->next;
	}
}

static int	hash_clear(t_shell *shell, char **ptr)
{
	char	*path;
	t_hlist	*hptr;
	int		code;

	while (*(++ptr) && (is_builtins(shell, *ptr, 0) || hash_clear(shell, ptr)))
	{
		code = hash_cmdtoint(*ptr);
		path = cmd_searchpath(*ptr, shell->env);
		if (path == NULL)
			hash_error(*ptr, 0);
		if (path && hash_check(*ptr, shell->htab, &code) == FAILURE)
		{
			shell->htab[code] = ft_strdup(path);
			hash_add(code, shell);
		}
		hptr = shell->hlist;
		while (hptr && path)
		{
			if (hptr->code == code)
				hptr->count = 0;
			hptr = hptr->next;
		}
		ft_strdel(&path);
	}
	return (0);
}

static int	hash_del(t_shell *shell, char **c)
{
	t_hlist *ptr;
	t_hlist *ptr2;

	while (*(++c) && (**c != '/' || hash_del(shell, c)))
	{
		ptr2 = NULL;
		ptr = shell->hlist;
		while (ptr)
		{
			if (ft_strequ(*c, ft_strrchr(shell->htab[ptr->code], '/') + 1))
			{
				ft_strdel(&(shell->htab[ptr->code]));
				if (ptr2)
					ptr2->next = ptr->next;
				else
					shell->hlist = ptr->next;
				free(ptr);
				return (hash_del(shell, c));
			}
			ptr2 = ptr;
			ptr = ptr->next;
		}
		hash_error(*c, 0);
	}
	return (0);
}

static int	hash_display_path(t_shell *shell, char **cc)
{
	t_hlist	*ptr;

	if (shell->cmd[2] == NULL || shell->cmd[2][0] == '-')
		bi_error(shell, "-t: option requires an argument");
	else if (*cc)
	{
		ptr = shell->hlist;
		while (ptr)
		{
			if (ft_strequ(*cc, ft_strrchr(shell->htab[ptr->code], '/') + 1))
			{
				ft_putstr((ft_strrchr(shell->htab[ptr->code], '/') + 1));
				ft_putchar('\t');
				ft_putendl(shell->htab[ptr->code]);
				return (hash_display_path(shell, cc + 1));
			}
			ptr = ptr->next;
		}
		hash_error(*cc, 0);
		return (hash_display_path(shell, cc + 1));
	}
	return (0);
}

int			bi_hash(t_shell *shell)
{
	char	**cc;

	cc = shell->cmd;
	if (shell->hlist == NULL && (cc[1] == NULL || hash_options(cc + 1, 2)))
		ft_putstr("hash: hash table empty\n");
	else if (cc[1] == NULL || (ft_strequ(cc[1], "--") && cc[2] == NULL))
		hash_display(shell, 1);
	else if (cc[1][0] != '-' || (ft_strequ("--", cc[1]) && cc++))
		hash_clear(shell, cc);
	else if (ft_strnequ("-r", cc[1], 2))
		hash_init(shell, 1);
	else if (ft_strequ("-l", cc[1]) && cc[2] == NULL)
		hash_display(shell, 0);
	else if (ft_strequ("-d", cc[1]) && cc[2] && cc[2][0] != '-')
		hash_del(shell, cc + 1);
	else if (ft_strequ("-t", cc[1]))
		hash_display_path(shell, cc + 2);
	else if (cc[1] && hash_options(cc + 1, 1) == 0)
		hash_error(cc[1], 1);
	return (SUCCESS);
}
