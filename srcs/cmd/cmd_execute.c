/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:27:57 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 17:52:50 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"
#include <sys/wait.h>

static int		cmd_checkaccess(char *path)
{
	if ((access(path, F_OK) == SUCCESS) && (access(path, X_OK) == SUCCESS))
		return (SUCCESS);
	return (FAILURE);
}

static char		*cmd_check_path(char ***paths, char **sale)
{
	int		i;
	char	*r_path;

	i = 0;
	while ((*paths)[i] != NULL)
	{
		if ((r_path = ft_strjoin((*paths)[i], *sale)) == NULL)
		{
			ft_strdel(sale);
			ft_freechartab(paths);
			return (err_malloc("In check_path", "r_path"));
		}
		if (cmd_checkaccess(r_path) == SUCCESS)
		{
			ft_strdel(sale);
			ft_freechartab(paths);
			return (r_path);
		}
		ft_strdel(&r_path);
		i++;
	}
	ft_strdel(sale);
	ft_freechartab(paths);
	return (NULL);
}

char			*cmd_searchpath(char *cmd, char **env)
{
	char	**paths;
	char	*r_path;
	char	*sale;

	if (cmd_checkaccess(cmd) == SUCCESS)
		return (cmd);
	if ((r_path = ft_getenv("PATH", env)) == NULL)
		return (NULL);
	if ((paths = ft_strsplit(r_path, ':')) == NULL)
		return (NULL);
	ft_strdel(&r_path);
	sale = ft_strjoin("/", cmd);
	return (cmd_check_path(&paths, &sale));
}

int				cmd_executeit(char **env, t_shell *shell, char *path)
{
	pid_t	forked;
	int		ret;

	ret = 0;
	if ((forked = fork()) == FAILURE)
		return (bi_error(shell, "I can't fork with you :("));
	if (forked == SUCCESS)
	{
		if (execve(path, shell->cmd, env) == FAILURE)
			exit(bi_error(shell, "Execution of the command failed"));
	}
	else
	{
		if (waitpid(forked, &ret, 0) == FAILURE)
			return (bi_error(shell, "I can't wait for this command. Sorry."));
	}
	if (WIFEXITED(ret) && (WEXITSTATUS(ret) == SUCCESS))
		return (SUCCESS);
	return (FAILURE);
}

int				cmd_execute(t_shell *shell, char **env)
{
	char	*path;
	int		ret;
	int		code;

	code = hash_cmdtoint(shell->cmd[0]);
	if (shell->htab[code] != NULL)
		hash_check(shell->cmd[0], shell->htab, &code);
	if (shell->htab[code] == NULL)
	{
		if (cmd_checkaccess(shell->cmd[0]) == SUCCESS)
			path = ft_strdup(shell->cmd[0]);
		else if ((path = cmd_searchpath(shell->cmd[0], env)) == NULL)
			return (bi_error(shell, "Unknown command"));
		shell->htab[code] = ft_strdup(path);
		ft_strdel(&path);
	}
	if (shell->cmd[0][0] != '/')
		hash_add(code, shell);
	ret = cmd_executeit(env, shell, shell->htab[code]);
	return (ret);
}
