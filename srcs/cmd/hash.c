/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 16:27:58 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 15:08:28 by elazarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"
#include "builtins.h"

void				hash_init(t_shell *info, int flag)
{
	t_hlist	*ptr;

	while (flag && info->hlist)
	{
		ptr = info->hlist;
		free(info->htab[ptr->code]);
		info->hlist = info->hlist->next;
		free(ptr);
	}
	if (flag)
		free(info->htab);
	info->htab = ft_memalloc(sizeof(char*) * 6000);
	info->hlist = NULL;
}

int					hash_check(char *cmd, char **htab, int *code)
{
	int		i;

	while (htab[*code])
	{
		i = 0;
		while (htab[*code][i] && cmd[0] != '/')
			i++;
		while (cmd[0] != '/' && htab[*code][i - 1] != '/' && i > 0)
			i--;
		if (ft_strequ(&(htab[*code][i]), cmd))
			return (SUCCESS);
		*code += 1;
	}
	return (FAILURE);
}

int					hash_cmdtoint(char *cmd)
{
	int		i;
	int		code;
	int		j;

	code = 0;
	i = 0;
	while (cmd[i])
		i++;
	while (i && cmd[i - 1] != '/')
		i--;
	j = i;
	while (cmd[i])
		code += cmd[i++];
	if (code)
	{
		code *= (cmd[i - 1] + cmd[j]);
		code = code % 5000;
	}
	if (code)
		return (code);
	return (0);
}

static int			init_hlist(t_shell *shell, int code)
{
	if ((shell->hlist = malloc(sizeof(t_hlist))) == NULL)
	{
		err_malloc("In init_hlist", "shell->hlist");
		return (FAILURE);
	}
	shell->hlist->code = code;
	shell->hlist->count = 1;
	shell->hlist->next = NULL;
	return (SUCCESS);
}

void				hash_add(int code, t_shell *shell)
{
	t_hlist	*ptr;

	ptr = shell->hlist;
	if (shell->hlist == NULL && (init_hlist(shell, code) == FAILURE))
		return ;
	while (ptr)
	{
		if (ptr->code == code)
		{
			ptr->count += 1;
			break ;
		}
		else if (ptr->next == NULL)
		{
			ptr = malloc(sizeof(t_hlist));
			ptr->code = code;
			ptr->count = 1;
			ptr->next = shell->hlist;
			shell->hlist = ptr;
			ptr = NULL;
		}
		else
			ptr = ptr->next;
	}
}
