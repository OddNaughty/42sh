/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 11:48:52 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/26 15:50:38 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "sh42.h"
#include "tools.h"
#include "builtins.h"
#include "env.h"

static void		test_cmd(t_lexer *lexer)
{
	size_t				i;
	extern t_builtins	g_bi_table[NBB];

	i = 0;
	while (i < NBB)
	{
		if (ft_strcmp(lexer->value, g_bi_table[i].cmd) == SUCCESS)
			break ;
		i++;
	}
}

static void		test_out(t_lexer *lexer)
{
	int					fd;

	fd = open(lexer->value, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		lexer->token = ERROR;
	else
		close(fd);
}

static void		test_in(t_lexer *lexer)
{
	if (access(lexer->value, R_OK))
		lexer->token = ERROR;
}

void			check_permission(t_lexer *lexer)
{
	ft_putendl(lexer->value);
	if (lexer->prev != NULL && lexer->prev->token == IN)
		test_in(lexer);
	else if (lexer->prev != NULL
				&& (lexer->prev->token == OUT || lexer->prev->token == AOUT))
		test_out(lexer);
	else
		test_cmd(lexer);
}
