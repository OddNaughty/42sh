/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 20:39:41 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 15:39:42 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"
#include "env.h"

char	**env_copyenv(void)
{
	char			**copy;
	extern char		**environ;

	if ((copy = ft_strtabdup(environ)) == NULL)
		return (NULL);
	save_env(copy, 1);
	return (copy);
}

int		env_findline(char *name, char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if ((ft_strncmp(env[i], name, ft_strlen(name) - 1) == SUCCESS)
			&& (env[i][ft_strlen(name)] == '='))
			return (i);
		i++;
	}
	return (FAILURE);
}

char	*ft_getenv(const char *name, char **env)
{
	int		line;
	char	*ret;

	if (((env == NULL) || (name == NULL)) ||
		((line = env_findline((char *)name, env)) == FAILURE))
		return (NULL);
	ret = ft_strdup(env[line] + ft_strlen(name) + 1);
	return (ret);
}

int		env_reallocone(char ***tab, char *str)
{
	char	**copy;
	int		i;

	if ((copy = malloc(sizeof(*copy) * (ft_chartablength((*tab)) + 2))) == NULL)
		return (FAILURE);
	i = 0;
	while ((*tab)[i])
	{
		if ((copy[i] = ft_strdup((*tab)[i])) == NULL)
			return (FAILURE);
		i++;
	}
	if ((copy[i] = ft_strdup(str)) == NULL)
		return (FAILURE);
	copy[i + 1] = NULL;
	ft_freechartab(tab);
	*tab = copy;
	return (SUCCESS);
}

int		env_minusone(char ***tab, char *str)
{
	char	**copy;
	int		i;
	int		j;
	int		line;

	if ((copy = malloc(sizeof(*copy) * ft_chartablength((*tab)))) == NULL)
		return (FAILURE);
	i = 0;
	j = 0;
	if ((line = env_findline(str, *tab)) == FAILURE)
		return (SUCCESS);
	while ((*tab)[i] != NULL)
	{
		if (i != line)
		{
			if ((copy[j] = ft_strdup((*tab)[i])) == NULL)
				return (FAILURE);
			j++;
		}
		i++;
	}
	copy[j] = NULL;
	ft_freechartab(tab);
	*tab = copy;
	return (SUCCESS);
}
