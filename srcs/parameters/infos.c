/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 21:01:11 by ffondane          #+#    #+#             */
/*   Updated: 2014/02/28 22:24:51 by ffondane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "parameters.h"
#include "builtins.h"

static void	print_version(void)
{
	ft_putstr("42sh, version ");
	ft_putstr(VERSION);
}

static void	fake_copyright(void)
{
	ft_putendl("free2use, 2014 42 Student");
}

void		parameters(t_shell *shell, char **argv)
{
	if (ft_strcmp(argv[1], "--version") == SUCCESS)
		version(shell);
	if (ft_strcmp(argv[1], "--help") == SUCCESS)
		help(shell);
	ft_putstr_fd(BINNAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putendl_fd(": invalid option", 2);
	help(shell);
}

void		version(t_shell *shell)
{
	if (shell != NULL)
	{
		print_version();
		ft_putchar('\n');
		fake_copyright();
		ft_putendl("developpers:");
		ft_putendl("\tCamille Wagner (cwagner)");
		ft_putendl("\tGeraud Garrigoux (mon_sbire)");
		ft_putendl("\tFlavien Fondanesche (ffondane)");
		ft_putendl("\tEmile Lazarov (elazarov)");
		exit(SUCCESS);
	}
}

void		help(t_shell *shell)
{
	if (shell != NULL)
	{
		ft_putendl("Usage: ./42sh [options]");
		ft_putendl("42sh options:");
		ft_putendl("\t--version");
		ft_putendl("\t--help");
		exit(SUCCESS);
	}
}
