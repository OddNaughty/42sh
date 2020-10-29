/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 17:30:21 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/25 20:06:22 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"

static int	son_in(t_tree *parser, t_shell **shell, int savein)
{
	int		in;
	char	**split;
	int		ret;

	ret = -1;
	if (parser->right->token == CMD)
	{
		if ((split = ft_strsplitwhite(parser->right->value)) == NULL)
			return (failure_error("MALLOC ERROR"));
		in = open(split[0], O_RDONLY);
		ft_freechartab(&split);
		if (in == FAILURE)
			return (failure_error("Can't open the file"));
		if (dup2(in, 0) == FAILURE)
			return (failure_error("Hmmmm, I can't read from this file"));
		ret = redir_cmd(parser->left, shell);
		if (dup2(savein, 0) == FAILURE)
			return (failure_error("Can't restore stdout..."));
		if ((close(in) == FAILURE) || (close(savein) == FAILURE))
			return (failure_error("Forget to close..."));
	}
	return (ret);
}

int			redir_in(t_tree *parser, t_shell **shell)
{
	int		savein;

	if ((savein = dup(0)) == FAILURE)
		return (failure_error("Can't save STDOUT"));
	return (son_in(parser, shell, savein));
}

int			redir_ain(t_tree *parser, t_shell **shell)
{
	(void)parser;
	(void)shell;
	return (SUCCESS);
}

int			redir_error(t_tree *parser, t_shell **shell)
{
	(void)shell;
	ft_putendl_fd(parser->value, 2);
	return (FAILURE);
}
