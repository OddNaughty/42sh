/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktoken_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 15:40:14 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/17 19:24:15 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh42.h"

int			is_and(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '&' || !tmp[1] || tmp[1] != '&')
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str) += 2;
	(*index) = 0;
	if (addtolex(lexer, "AND", AND) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int			is_or(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != '|' || !tmp[1] || tmp[1] != '|')
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str) += 2;
	(*index) = 0;
	if (addtolex(lexer, "OR", OR) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int			is_coma(t_lexer **lexer, char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	if (tmp[0] != ';')
		return (NO);
	if (addcmd(lexer, *str, *index) == FAILURE)
		return (FAILURE);
	(*str)++;
	(*index) = 0;
	if (addtolex(lexer, "COMA", COMA) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
