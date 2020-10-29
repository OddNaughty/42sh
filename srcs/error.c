/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 14:41:52 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/25 19:23:47 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "sh42.h"

void			*err_malloc(char *str, char *varname)
{
	ft_putstr_fd("Malloc error: ", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}

static void		ft_puttoken(int token)
{
	if (token == COMA)
		ft_putendl_fd("\";\"", 2);
	else if (token == AND)
		ft_putendl_fd("\"&&\"", 2);
	else if (token == OR)
		ft_putendl_fd("\"||\"", 2);
	else if (token == PIPE)
		ft_putendl_fd("\"|\"", 2);
	else if (token == AIN)
		ft_putendl_fd("\"<<\"", 2);
	else if (token == OUT)
		ft_putendl_fd("\">\"", 2);
	else if (token == AOUT)
		ft_putendl_fd("\">>\"", 2);
	else if (token == IN)
		ft_putendl_fd("\"<\"", 2);
	else if (token == OUT)
		ft_putendl_fd("\">\"", 2);
}

int				syntax_error(t_lexer *lexer)
{
	ft_putstr_fd("Syntax error near: ", 2);
	if (lexer->prev != NULL && lexer->prev->token != CMD)
		ft_puttoken(lexer->prev->token);
	else if (lexer != NULL && lexer->token != CMD)
		ft_puttoken(lexer->token);
	else if (lexer->next != NULL && lexer->next->token != CMD)
		ft_puttoken(lexer->next->token);
	else
		ft_puttoken(lexer->token);
	return (FAILURE);
}

int				failure_error(char *str)
{
	ft_putstr_fd("42sh: FATAL: ", 2);
	ft_putendl_fd(str, 2);
	return (FAILURE);
}
