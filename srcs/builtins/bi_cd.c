/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 16:38:47 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/26 15:41:43 by ffondane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include <stdlib.h>
#include "libft.h"
#define HOMETILDE (shell->cmd[pos][0] == '~')

int		is_home(t_shell *shell, int pos)
{
	if (shell->cmd[pos] == NULL)
		return (0);
	if (HOMETILDE && shell->cmd[pos][1] == '\0')
		return (0);
	if (HOMETILDE && shell->cmd[pos][1] == '/' && shell->cmd[pos][2] == '\0')
		return (0);
	return (-1);
}

int		is_homepath(t_shell *shell, int pos)
{
	if (shell->cmd[pos] == NULL)
		return (-1);
	if (HOMETILDE && shell->cmd[pos][1] == '/' && shell->cmd[pos][2] != '\0')
		return (0);
	return (-1);
}

int		is_opts(t_shell *shell)
{
	char	*err;
	char	*tmp;

	err = NULL;
	if (shell->cmd[1] == NULL)
		return (0);
	if (ft_strcmp(shell->cmd[1], "-l") == 0)
		return (2);
	if (shell->cmd[1][0] == '-' && shell->cmd[1][1] != '\0')
	{
		err = ft_strdup(shell->cmd[1]);
		tmp = ft_strjoin(err, ": invalid option");
		free(err);
		err = ft_strjoin(tmp, "\ncd: usage: cd [-l] [dir]");
		bi_error(shell, err);
		free(err);
		free(tmp);
		return (-1);
	}
	return (0);
}

int		is_back(t_shell *shell, int pos)
{
	if (shell->cmd[pos] == NULL)
		return (-1);
	if (shell->cmd[pos][0] == '-' && shell->cmd[pos][1] == '\0')
		return (0);
	return (-1);
}
