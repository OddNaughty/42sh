/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:21:26 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/26 13:38:42 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

t_termios		save_term(struct termios termios, int rw)
{
	static struct termios	term_save;

	if (rw == 1)
		term_save = termios;
	return (term_save);
}

void			set_termios(void)
{
	struct termios		term;
	char				*term_name;

	if ((term_name = getenv("TERM")) == NULL)
	{
		ft_putendl_fd("Cant work without environement.", 2);
		exit(-1);
	}
	if ((tgetent(NULL, term_name)) == ERR)
		exit(-1);
	if (tcgetattr(0, &term) == -1)
		exit(-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		exit(-1);
}

void			restore_termios(void)
{
	struct termios		term;

	term = save_term(term, 0);
	tcsetattr(0, TCSANOW, &term);
}
