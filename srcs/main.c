/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 11:33:32 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 20:31:58 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "lexer.h"
#include "parser.h"
#include "sh_termcaps.h"
#include "libft.h"
#include "env.h"
#include "builtins.h"
#include "parameters.h"

static t_shell	*init_info(int argc, char **argv)
{
	t_shell		*info;

	if ((info = malloc(sizeof(*info))) == NULL)
		return (err_malloc("In main", "info"));
	if (argc == 2)
		parameters(info, argv);
	info->env = env_copyenv();
	info->cmdret = 0;
	set_shell(info);
	signal_init();
	return (info);
}

static void		donormshit(t_tree *parser, t_lexer *lexed,
							t_shell *info, char *line)
{
	int		i;

	i = 0;
	if (((info->str = line) != NULL) && (*line))
	{
		while (line[i] && ((line[i] == ' ') || (line[i] == '\t')))
			i++;
		if (line[i])
		{
			lexed = lexit(info->str);
			if ((parser = parseit(&lexed)) != NULL)
			{
				info->cmdret = dotree(parser, &info);
				free_lexer(&lexed);
				free_parser(&parser);
				if (line != NULL)
					ft_strdel(&line);
			}
		}
		else
			info->cmdret = 0;
	}
	else
		info->cmdret = 0;
}

int				main(int argc, char **argv)
{
	char	*line;
	t_shell	*info;
	t_lexer	*lexed;
	t_tree	*parser;

	lexed = NULL;
	parser = NULL;
	if ((info = init_info(argc, argv)) == NULL)
		return (FAILURE);
	while (1)
	{
		line = NULL;
		set_termios();
		signal_init();
		if (input_line(&line) != SUCCESS)
			return (FAILURE);
		restore_termios();
		set_signal_cmd();
		donormshit(parser, lexed, info, line);
	}
	return (SUCCESS);
}
