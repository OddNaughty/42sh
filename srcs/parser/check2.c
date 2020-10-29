/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 14:44:38 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 20:54:31 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "sh42.h"

void			count_token(t_state *state, t_lexer *lexer)
{
	if (lexer->token == PIPE)
	{
		if (state->out >= 1)
			state->out = 2;
		else
			state->pipes++;
	}
	else if (lexer->token == AIN || lexer->token == IN)
	{
		if (state->out >= 1)
			state->out = 2;
		if (state->pipes > 0)
			state->out = 2;
		else
			state->in++;
	}
	else if (lexer->token == AOUT || lexer->token == OUT)
		state->out++;
}

static int		pipe_error(void)
{
	ft_putendl_fd("Too much or ambiguous redirections.", 2);
	return (FAILURE);
}

int				check_redir(t_state *state, t_lexer *lexer)
{
	count_token(state, lexer);
	if (state->out > 1)
		return (pipe_error());
	if (state->in > 1)
		return (pipe_error());
	if (state->pipes > MAX_PIPES)
		return (pipe_error());
	else
		return (SUCCESS);
}
