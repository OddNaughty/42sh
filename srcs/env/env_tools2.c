/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 10:35:50 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/25 20:17:51 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "sh42.h"

int		env_changeline(char ***env, char **line, int i)
{
	if (i == -1)
		i = env_reallocone(env, *line);
	else
	{
		ft_strdel(&((*env)[i]));
		(*env)[i] = ft_strdup(*line);
	}
	ft_strdel(line);
	if (i == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

char	**save_env(char **new_env, int rw)
{
	static char		**cpy_env = NULL;

	if (rw == 1)
		cpy_env = new_env;
	return (cpy_env);
}
