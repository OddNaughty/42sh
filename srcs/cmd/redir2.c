/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 16:19:14 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 17:40:41 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"

static int	son_aout(t_tree *parser, t_shell **shell, int saveaout)
{
	int		in;
	char	**split;
	int		ret;

	ret = -1;
	if ((split = ft_strsplitwhite(parser->right->value)) == NULL)
		return (failure_error("MALLOC ERROR"));
	in = open(split[0], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_freechartab(&split);
	if (in == FAILURE)
		return (failure_error("Can't create/open the file"));
	if (dup2(in, 1) == FAILURE)
		return (failure_error("Hmmmm, I can't write on this file"));
	ret = dotree(parser->left, shell);
	if (dup2(saveaout, 1) == FAILURE)
		return (failure_error("Can't restore stdin..."));
	if ((close(in) == FAILURE) || (close(saveaout) == FAILURE))
		return (failure_error("Forget to close..."));
	return (ret);
}

int			redir_aout(t_tree *parser, t_shell **shell)
{
	int		savein;

	if ((savein = dup(1)) == FAILURE)
		return (failure_error("Can't save STDIN"));
	return (son_aout(parser, shell, savein));
}

static int	son_out(t_tree *parser, t_shell **shell, int saveout)
{
	int		in;
	char	**split;
	int		ret;

	ret = -1;
	if ((split = ft_strsplitwhite(parser->right->value)) == NULL)
		return (failure_error("MALLOC ERROR"));
	in = open(split[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	ft_freechartab(&split);
	if (in == FAILURE)
		return (failure_error("Can't create/open the file"));
	if (dup2(in, 1) == FAILURE)
		return (failure_error("Hmmmm, I can't write on this file"));
	ret = dotree(parser->left, shell);
	if (dup2(saveout, 1) == FAILURE)
		return (failure_error("Can't restore stdin..."));
	if ((close(in) == FAILURE) || (close(saveout) == FAILURE))
		return (failure_error("Forget to close..."));
	return (ret);
}

int			redir_out(t_tree *parser, t_shell **shell)
{
	int		saveout;

	if ((saveout = dup(1)) == FAILURE)
		return (failure_error("Can't save STDIN"));
	return (son_out(parser, shell, saveout));
}

int			redir_cmd(t_tree *parser, t_shell **shell)
{
	char	**split;
	int		ret;

	if (!parser)
		return (FAILURE);
	if ((split = ft_strsplitwhite(parser->value)) == NULL)
		return (FAILURE);
	(*shell)->cmd = split;
	ret = is_builtins(*shell, NULL, 1);
	if (ret == 1)
		ret = cmd_execute(*shell, (*shell)->env);
	if ((*shell)->cmd)
		ft_freechartab(&split);
	return (ret);
}
