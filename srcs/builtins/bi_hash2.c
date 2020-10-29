/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elazarov <elazarov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 22:34:04 by elazarov          #+#    #+#             */
/*   Updated: 2014/03/27 15:39:16 by elazarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

void	hash_error(char *arg, int fg)
{
	if (fg)
	{
		if (arg[1] != 'd' && arg[1] != 'l' && arg[1] != 't')
		{
			ft_putstr_fd(BINNAME, 2);
			ft_putstr_fd(": hash: ", 2);
			write(2, arg, 2);
			ft_putendl_fd(": invalid option", 2);
		}
		ft_putstr_fd(BINNAME, 2);
		ft_putendl_fd(": usage: hash [-lr] [-dt] [name ...]", 2);
	}
	else
	{
		ft_putstr_fd(BINNAME, 2);
		ft_putstr_fd(": hash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": not found", 2);
	}
}

int		hash_options(char **cmd, int fg)
{
	char	*ptr;

	if (ft_strequ(*cmd, "--"))
	{
		if (fg < 2 || cmd[1] == NULL)
			return (1);
		if (fg == 2 && ft_strequ(*cmd, "--") && cmd[1])
			return (0);
	}
	while (*cmd && **cmd == '-' && ft_strchr((*cmd) + 1, '-') == NULL)
	{
		ptr = *cmd;
		while (*(++ptr))
		{
			if (*ptr != 'd' && *ptr != 'l' && fg)
				return (0);
			if (fg == 1 && *ptr != 't' && *ptr != 'r')
				return (0);
		}
		cmd++;
	}
	if (*cmd && fg == 2)
		return (0);
	return (1);
}
