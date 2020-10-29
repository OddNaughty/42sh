/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 15:40:10 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 20:40:41 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "sh42.h"

static int		is_cmd(t_lexer *lexer)
{
	size_t			index;

	index = 0;
	if (lexer->token != CMD)
		return (FAILURE);
	else
	{
		while (lexer->value[index])
		{
			if (lexer->value[index] != ' ' && lexer->value[index] != '\t')
				return (SUCCESS);
			index++;
		}
		return (FAILURE);
	}
}

static int		check_token_state(t_lexer *lexer, int state)
{
	if (state == 0 && is_cmd(lexer) == SUCCESS)
		return (1);
	else if (state == 1 && lexer->token != CMD)
		return (0);
	else
		return (-1);
}

static int		check_token_state_end(t_lexer *lexer, int state)
{
	if (state == 1 && lexer->token == COMA)
	{
		return (SUCCESS);
	}
	else if (state == 1)
		return (syntax_error(lexer));
	else if (is_cmd(lexer) == FAILURE)
		return (syntax_error(lexer));
	else
	{
		return (SUCCESS);
	}
}

static t_state	state_init(t_state state)
{
	state.out = 0;
	state.in = 0;
	state.pipes = 0;
	return (state);
}

int				checksyntax(t_lexer **lexer)
{
	t_lexer		*tmp;
	t_state		redir;
	int			state;

	tmp = *lexer;
	redir = state_init(redir);
	state = 0;
	if (is_cmd(tmp) == SUCCESS)
		state = 1;
	else if ((tmp->token != COMA) && (tmp->token != CMD))
		return (syntax_error(tmp));
	tmp = tmp->next;
	if (!tmp || (state == 1 && tmp == NULL))
		return (SUCCESS);
	while (tmp->next)
	{
		state = check_token_state(tmp, state);
		if (state == -1)
			return (syntax_error(tmp));
		if (check_redir(&redir, tmp) == FAILURE)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (check_token_state_end(tmp, state));
}
