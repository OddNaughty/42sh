/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:14:52 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/26 17:31:58 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "sh42.h"

static int	checktoken(t_lexer **lexer, char **str, int *len)
{
	int			i;
	int			ret;
	static int	(*checktokens[NBR_TOK - 2])(t_lexer **l, char **s, int *i) =

	{
	is_pipe,
	is_out,
	is_aout,
	is_in,
	is_ain,
	is_and,
	is_or,
	is_coma
	};
	i = 0;
	while ((i < (NBR_TOK - 2))
			&& (ret = checktokens[i](lexer, str, len) != SUCCESS))
	{
		if (ret == FAILURE)
			return (FAILURE);
		i++;
	}
	if (i == (NBR_TOK - 2))
		return (NO);
	return (SUCCESS);
}

static void	shit_quotes(char **str, int *len)
{
	(*str)++;
	(*len)++;
	while (**str && (**str != '"'))
	{
		(*str)++;
		(*len)++;
	}
}

int			addcmd(t_lexer **lexer, char *str, int i)
{
	char	*sub;
	int		ret;

	if ((sub = ft_strsub(str - i, 0, i)) == NULL)
		return (FAILURE);
	if (!*sub)
		return (SUCCESS);
	ret = addtolex(lexer, sub, CMD);
	ft_strdel(&sub);
	return (ret);
}

t_lexer		*lexit(char *str)
{
	t_lexer	*list;
	int		ret;
	int		len;

	list = NULL;
	len = 0;
	while (*str)
	{
		if (*str == '"')
			shit_quotes(&str, &len);
		ret = checktoken(&list, &str, &len);
		if (ret == FAILURE)
			return (NULL);
		if (ret != SUCCESS)
		{
			str++;
			len++;
		}
	}
	if (ret != SUCCESS)
		addcmd(&list, str, len);
	return (list);
}
