/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 17:19:08 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/03 16:56:07 by ffondane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

int			bi_pwd(t_shell *shell)
{
	char	*pwd;

	if (shell != NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (bi_error(shell, "getcwd error"));
		else
			ft_putendl(pwd);
	}
	return (SUCCESS);
}

int			bi_read(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("read: not implemented yet");
	}
	return (SUCCESS);
}

int			bi_job(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("job: not implemented yet");
	}
	return (SUCCESS);
}

int			bi_fg(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("fg: not implemented yet");
	}
	return (SUCCESS);
}

int			bi_bg(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("bg: not implemented yet");
	}
	return (SUCCESS);
}
