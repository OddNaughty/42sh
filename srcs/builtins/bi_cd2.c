/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 12:30:45 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/27 16:49:58 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include <stdlib.h>
#include "libft.h"
#include "tools.h"

int				check_chdir(char *path, char **err)
{
	char		*sale;
	int			ret;

	ret = 0;
	if (access(path, F_OK) == -1)
	{
		sale = ft_strdup("no such file or directory: ");
		*err = ft_strjoin(sale, path);
		ret = -1;
	}
	if ((ret != FAILURE) && (is_directory(path) == 1))
	{
		sale = ft_strdup("not a directory: ");
		*err = ft_strjoin(sale, path);
		ret = -1;
	}
	if ((ret != FAILURE) && (access(path, X_OK) == -1))
	{
		sale = ft_strdup("permission denied: ");
		*err = ft_strjoin(sale, path);
		ret = -1;
	}
	if (ret == -1)
		ft_strdel(&sale);
	return (ret);
}

int				do_chdir(t_shell *shell, char *path, int opts)
{
	int			ret;
	char		*cwd;
	char		*err;

	cwd = getcwd(NULL, MAXPATHLEN);
	err = NULL;
	ret = check_chdir(path, &err);
	if (ret == 0)
		ret = chdir(path);
	if (ret == 0)
	{
		bi_dosetenv(&(shell->env), "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		bi_dosetenv(&(shell->env), "PWD", cwd);
	}
	if (ret == -1)
	{
		ret = bi_error(shell, err);
		free(err);
	}
	if (opts == 2 && ret == 0)
		ft_putendl(cwd);
	free(cwd);
	return (ret);
}

int				do_fromhome_chdir(t_shell *shell, int opts, int pos)
{
	char		*path;
	char		*tmp;
	int			ret;

	path = ft_getenv("HOME", shell->env);
	tmp = ft_strsub(shell->cmd[pos], 1, ft_strlen(shell->cmd[pos]));
	path = ft_strjoin(path, tmp);
	ret = do_chdir(shell, path, opts);
	ft_free3char(&path, &tmp, NULL);
	return (ret);
}

int				do_special_chdir(t_shell *shell, int opts, int to)
{
	char		*path;
	int			ret;

	if (to == 0)
		path = ft_getenv("HOME", shell->env);
	else
		path = ft_getenv("OLDPWD", shell->env);
	ret = do_chdir(shell, path, opts);
	free(path);
	return (ret);
}

int				bi_cd(t_shell *shell)
{
	int			opts;
	int			pos;

	pos = 1;
	opts = is_opts(shell);
	if (opts > 0)
		pos = 2;
	if (opts == -1)
		return (-1);
	if (is_home(shell, pos) == 0)
		return (do_special_chdir(shell, pos, 0));
	if (is_back(shell, pos) == 0)
		return (do_special_chdir(shell, pos, 1));
	if (is_homepath(shell, pos) == 0)
		return (do_fromhome_chdir(shell, opts, pos));
	return (do_chdir(shell, shell->cmd[pos], opts));
}
