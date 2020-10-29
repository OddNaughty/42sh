/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 19:34:51 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 13:49:36 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "sh42.h"
#include "libft.h"

static t_lexer	*lexersplit_token(t_lexer **lexer, int token)
{
	t_lexer		*tmp;
	t_lexer		*lexer_2;

	tmp = *lexer;
	while (tmp != NULL)
	{
		if ((tmp->token == token) && (tmp->next))
		{
			lexer_2 = tmp->next;
			lexer_2->prev = NULL;
			if (tmp->prev)
			{
				tmp->prev->next = NULL;
				lex_freeone(tmp);
			}
			else
				*lexer = NULL;
			return (lexer_2);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_tree			*initnode(int token, t_tree *father)
{
	t_tree		*new;

	new = malloc(sizeof(*new));
	new->right = NULL;
	new->left = NULL;
	new->parent = father;
	new->value = NULL;
	new->token = token;
	return (new);
}

t_tree			*buildtree(t_lexer **lexer, int token, t_tree *father)
{
	t_tree	*parser;
	t_lexer	*lex2;

	parser = initnode(token, father);
	if ((token == CMD) && (*lexer))
	{
		parser->value = ft_strdup((*lexer)->value);
		parser->token = (*lexer)->token;
		free_lexer(lexer);
		return (parser);
	}
	lex2 = lexersplit_token(lexer, token);
	if (lex2 != NULL)
	{
		if (*lexer)
			parser->left = buildtree(lexer, token + 1, parser);
		parser->right = buildtree(&lex2, token, parser);
	}
	else
	{
		free_parser(&parser);
		return (buildtree(lexer, ++token, father));
	}
	return (parser);
}

t_tree			*parseit(t_lexer **lexer)
{
	t_tree		*parser;

	if (checksyntax(lexer) == FAILURE)
		return (NULL);
	parser = buildtree(lexer, COMA, NULL);
	return (parser);
}
