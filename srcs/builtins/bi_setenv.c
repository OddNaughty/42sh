/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 14:33:28 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/03 15:09:14 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "env.h"

int		bi_dosetenv(char ***env, char *key, char *value)
{
	int		i;
	char	*sale;
	char	*line;

	i = env_findline(key, *env);
	if ((sale = ft_strjoin(key, "=")) == NULL)
		return (FAILURE);
	if ((line = ft_strjoin(sale, value)) == NULL)
	{
		ft_strdel(&sale);
		return (FAILURE);
	}
	ft_strdel(&sale);
	if (env_changeline(env, &line, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
