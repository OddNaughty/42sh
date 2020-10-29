/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 12:25:42 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 14:09:44 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "lexer.h"
#include "parser.h"
#include "libft.h"

void		free_lexer(t_lexer **lex)
{
	if (!*lex)
		return ;
	free_lexer(&((*lex)->next));
	ft_strdel(&(*lex)->value);
	(*lex)->prev = NULL;
	(*lex)->next = NULL;
	free(*lex);
	*lex = NULL;
}

void		free_parser(t_tree **parser)
{
	if (!*parser)
		return ;
	free_parser(&((*parser)->left));
	free_parser(&((*parser)->right));
	ft_strdel(&((*parser)->value));
	(*parser)->right = NULL;
	(*parser)->left = NULL;
	(*parser)->parent = NULL;
	free(*parser);
	*parser = NULL;
}
