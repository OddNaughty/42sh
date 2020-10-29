/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 22:04:41 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/26 16:17:30 by ffondane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "sh42.h"

int			bi_error(t_shell *shell, char *msg)
{
	ft_putstr_fd(BINNAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(shell->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (FAILURE);
}

void		ft_free3char(char **one, char **two, char **three)
{
	if (one != NULL)
	{
		free(*one);
		*one = NULL;
	}
	if (two != NULL)
	{
		free(*two);
		*two = NULL;
	}
	if (three != NULL)
	{
		free(*three);
		*three = NULL;
	}
}
