/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:50:52 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/26 15:19:51 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>

static int	son_pipe(t_tree *parser, t_shell **shell, int piped[2])
{
	int		ret;

	if (dup2(piped[1], 1) == FAILURE)
		exit(failure_error("Level dup !"));
	ret = dotree(parser->left, shell);
	if (close(piped[0]) == FAILURE)
		exit(failure_error("It was close to work. JAJAJAJA"));
	exit(ret);
}

static int	father_pipe(t_tree *parser, t_shell **shell, int piped[2])
{
	int		ret;

	if (dup2(piped[0], 0) == FAILURE)
		exit(failure_error("Level dup !"));
	if (close(piped[1]) == FAILURE)
		exit(failure_error("It was close to work. JAJAJAJA"));
	ret = dotree(parser->right, shell);
	if (wait(NULL) == FAILURE)
		exit(failure_error("Can't wait for the father pipe"));
	exit(ret);
}

static int	do_bigfork(t_tree *parser, t_shell **shell)
{
	pid_t		forked;
	int			piped[2];

	if (pipe(piped) == FAILURE)
		return (failure_error("BLOWJOB FAILED"));
	if ((forked = fork()) == FAILURE)
		return (failure_error("I can't fork with you"));
	else if (!forked)
		son_pipe(parser, shell, piped);
	else
		father_pipe(parser, shell, piped);
	return (SUCCESS);
}

int			redir_pipe(t_tree *parser, t_shell **shell)
{
	pid_t	bigfork;
	int		ret;

	ret = 0;
	if ((bigfork = fork()) == FAILURE)
		return (failure_error("I can't fork with you"));
	if (!bigfork)
	{
		if (do_bigfork(parser, shell) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (waitpid(bigfork, &ret, 0) == FAILURE)
			return (failure_error("Can't wait for it"));
	}
	if (WIFEXITED(ret) && (WEXITSTATUS(ret) == SUCCESS))
		return (SUCCESS);
	return (FAILURE);
}
