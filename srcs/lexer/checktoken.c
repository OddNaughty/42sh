/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktoken.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 15:32:40 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/17 19:20:19 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh42.h"

int			is_pipe(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '|')
		return (NO);
	if (tmp[1] && (tmp[1] == '|'))
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str)++;
	(*index) = 0;
	if (addtolex(lexer, "PIPE", PIPE) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int			is_out(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '>')
		return (NO);
	if (tmp[1] && (tmp[1] == '>'))
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str)++;
	(*index) = 0;
	if (addtolex(lexer, "OUT", OUT) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int			is_aout(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '>' || !tmp[1] || tmp[1] != '>')
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str) += 2;
	(*index) = 0;
	if (addtolex(lexer, "AOUT", AOUT) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int			is_in(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '<')
		return (NO);
	if (tmp[1] && (tmp[1] == '<'))
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str)++;
	(*index) = 0;
	if (addtolex(lexer, "IN", IN) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int			is_ain(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '<' || !tmp[1] || tmp[1] != '<')
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str) += 2;
	(*index) = 0;
	if (addtolex(lexer, "AIN", AIN) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
