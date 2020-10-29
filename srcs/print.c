/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 17:12:40 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 11:31:29 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

static void		norme(t_tree *tree, int i, char *tokens[10])
{
	int			cmp;

	cmp = 0;
	while (cmp++ < i)
		ft_putchar('\t');
	if (tree->value)
	{
		ft_putstr(tree->value);
		ft_putstr(" == ");
	}
	ft_putendl(tokens[tree->token - 1]);
	cmp = 0;
	while (cmp++ < i)
		ft_putchar('\t');
	ft_putchar('|');
	ft_putendl("");
}

void			printtree(t_tree *tree, int i)
{
	static char	*tokens[10] =

	{
	"COMA",
	"AND",
	"OR",
	"PIPE",
	"OUT",
	"AOUT",
	"AIN",
	"IN",
	"CMD",
	"NULL"};
	if (tree)
	{
		norme(tree, i, tokens);
		if (tree->left)
			printtree(tree->left, i + 1);
		if (tree->right)
			printtree(tree->right, i + 1);
	}
}
