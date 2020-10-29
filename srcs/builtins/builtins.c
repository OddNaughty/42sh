/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 22:40:22 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/27 17:54:48 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh_termcaps.h"
#include "libft.h"
#include "env.h"
#include "builtins_struct.h"

int			is_builtins(t_shell *shell, char *cc, int fg)
{
	int					i;
	extern t_builtins	g_bi_table[NBB];

	i = 0;
	if ((shell != NULL) && (shell->cmd[0] != NULL))
	{
		while (i < NBB)
		{
			if (fg && ft_strcmp((shell->cmd)[0], g_bi_table[i].cmd) == SUCCESS)
				return (g_bi_table[i].f_bi(shell));
			else if (fg == 0 && ft_strcmp(cc, g_bi_table[i].cmd) == SUCCESS)
				return (0);
			i++;
		}
		return (1);
	}
	return (-1);
}

int			bi_env(t_shell *shell)
{
	char	**split;

	split = shell->cmd;
	if (split[0] && !split[1])
	{
		if (shell->env != NULL)
		{
			ft_printtabchar(shell->env);
			return (SUCCESS);
		}
		ft_putendl("env: is empty");
		return (SUCCESS);
	}
	else if (ft_strcmp(split[1], "-i") == SUCCESS)
	{
		shell->cmd += 2;
		if (!shell->cmd[1])
			return (SUCCESS);
		shell->cmd[0] = cmd_searchpath(shell->cmd[0], shell->env);
		return (cmd_executeit(NULL, shell, shell->cmd[0]));
	}
	return (FAILURE);
}

int			bi_exit(t_shell *shell)
{
	if (shell != NULL)
	{
		if (ft_strlen(shell->cmd[1]) > 0)
		{
			if (ft_strcheck(shell->cmd[1], ft_isdigit) == SUCCESS)
			{
				restore_shell();
				exit(ft_atoi(shell->cmd[1]));
			}
			else
				return (bi_error(shell, "numeric argument required"));
		}
		else
		{
			restore_shell();
			exit(shell->cmdret);
		}
	}
	return (-1);
}

int			bi_setenv(t_shell *shell)
{
	char				**split;

	split = shell->cmd;
	if (ft_chartablength(split) > 3)
		return (bi_error(shell, "Too many arguments"));
	if (split[1] == NULL)
		return (bi_error(shell, "Setenv need arguments"));
	return (bi_dosetenv(&(shell->env), split[1], split[2]));
}

int			bi_unsetenv(t_shell *shell)
{
	char				**split;
	int					i;

	split = shell->cmd;
	if (split[1] == NULL)
		return (bi_error(shell, "Unsetenv need arguments"));
	i = 1;
	while (split[i])
	{
		if (env_minusone(&(shell->env), split[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
