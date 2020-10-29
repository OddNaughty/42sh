/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 14:42:33 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/26 18:01:56 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

int			dotree(t_tree *parser, t_shell **shell)
{
	static int	(*redir[NBR_TOK])(t_tree *parser, t_shell **shell) =

	{
	redir_coma,
	redir_and,
	redir_or,
	redir_pipe,
	redir_out,
	redir_aout,
	redir_ain,
	redir_in,
	redir_cmd,
	redir_error
	};
	if (!parser)
		return (SUCCESS);
	if ((redir[parser->token - 1](parser, shell)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
