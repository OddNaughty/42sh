/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 17:05:38 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 19:31:49 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "builtins.h"

static int		check_echo_args(char *args)
{
	size_t			index;
	int				n;
	int				e;

	index = 0;
	n = 0;
	e = 0;
	if (args[index] != '-')
		return (-1);
	index++;
	while (args[index])
	{
		if (args[index] == 'n')
			n = 1;
		else if (args[index] == 'e')
			e = 2;
		else if (args[index] == 'E')
			e = 4;
		else
			return (-1);
		index++;
	}
	return (n + e);
}

static void		ft_putstr_no_escaped(char **line, size_t start)
{
	while (line[start] != NULL)
	{
		ft_putstr(line[start]);
		if (line[start + 1] != NULL)
			ft_putchar(' ');
		start++;
	}
}

int				bi_echo(t_shell *shell)
{
	int				args;

	args = 0;
	if (shell->cmd[1] == NULL)
		return (1);
	args = check_echo_args(shell->cmd[1]);
	if (args == 2 || args == 3)
		ft_putstr_escaped(shell->cmd, 2);
	else if (args == 1 || args == 4 || args == 5)
		ft_putstr_no_escaped(shell->cmd, 2);
	else
		ft_putstr_no_escaped(shell->cmd, 1);
	if (args != 1 && args != 3 && args != 5)
		write(1, "\n", 1);
	return (0);
}
