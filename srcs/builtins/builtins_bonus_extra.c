/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 22:40:22 by ffondane          #+#    #+#             */
/*   Updated: 2014/02/28 17:33:57 by ffondane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

int			bi_unset(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("unset: not implemented yet");
	}
	return (SUCCESS);
}

int			bi_export(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("export: not implemented yet");
	}
	return (SUCCESS);
}
