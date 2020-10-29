/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 16:53:20 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 20:54:07 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include <signal.h>
#include "libft.h"

void			ft_handle_signal2(int signal)
{
	write(1, "\b\b", 2);
	signal++;
}

void			ft_handle_signal(int signal)
{
	char			**line;
	t_cursor		*cursor;

	if (signal == SIGINT)
	{
		line = save_line_ptr(NULL, 0);
		cursor = save_cursor_ptr(NULL, 0);
		ft_putchar('\n');
		ft_putuser();
		ft_bzero(*line, BUFF_SIZE);
		cursor->string = 0;
		cursor->strlen = 0;
		signal++;
	}
}

void			handle_seg(int signal)
{
	restore_shell();
	ft_putstr_fd("Congratulations, you found the ", 2);
	ft_putendl_fd("secret way to exit this shell!", 2);
	ft_putendl_fd("Camille: Batard saugrenu, tu paieras pour ca", 2);
	exit(1);
	signal++;
}

void			signal_init(void)
{
	signal(SIGWINCH, ft_resize_signal);
	signal(SIGINT, ft_handle_signal);
	signal(SIGSEGV, handle_seg);
	signal(SIGTERM, ft_handle_critic);
	signal(SIGSTOP, ft_handle_critic);
	signal(SIGBUS, ft_handle_critic);
	signal(SIGQUIT, ft_handle_critic);
}

void			ft_resize_signal(int signal)
{
	char			**line;
	t_cursor		*cursor;

	line = save_line_ptr(NULL, 0);
	cursor = save_cursor_ptr(NULL, 0);
	while (key_is_left(line, cursor) != 1)
		;
	signal++;
}
