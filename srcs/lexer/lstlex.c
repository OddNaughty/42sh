/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:39:38 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/19 19:34:23 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "lexer.h"
#include "libft.h"

static t_lexer	*newlex(char *str, int tok)
{
	t_lexer	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (err_malloc("Can't create a new link", "new"));
	if ((new->value = ft_strdup(str)) == NULL)
		return (err_malloc("ft_strdup failed", "new->value"));
	new->token = tok;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int				addtolex(t_lexer **lexer, char *value, int token)
{
	static t_lexer	*tmp;
	t_lexer			*new;

	if ((new = newlex(value, token)) == NULL)
		return (FAILURE);
	if (*lexer == NULL)
	{
		*lexer = new;
		tmp = *lexer;
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void			lex_freeone(t_lexer *tmp)
{
	ft_strdel(&(tmp->value));
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp);
}

void			printlex(t_lexer **lexed)
{
	t_lexer *tmp;

	tmp = *lexed;
	while (tmp != NULL)
	{
		ft_putchar('[');
		ft_putstr(tmp->value);
		ft_putchar(']');
		ft_putchar('[');
		ft_putnbr(tmp->token);
		ft_putchar(']');
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
