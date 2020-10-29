/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 19:57:12 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/25 20:04:09 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

int		redir_and(t_tree *parser, t_shell **shell)
{
	if (dotree(parser->left, shell) == SUCCESS)
		return (dotree(parser->right, shell));
	return (FAILURE);
}

int		redir_or(t_tree *parser, t_shell **shell)
{
	if (dotree(parser->left, shell) == FAILURE)
		return (dotree(parser->right, shell));
	return (SUCCESS);
}

int		redir_coma(t_tree *parser, t_shell **shell)
{
	dotree(parser->left, shell);
	dotree(parser->right, shell);
	return (SUCCESS);
}
