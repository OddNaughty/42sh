/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:21:34 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 20:54:54 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"
#include <signal.h>

void			set_signal_cmd(void)
{
	signal(SIGINT, ft_handle_signal2);
}

void			ft_handle_critic(int signal)
{
	restore_shell();
	ft_putstr("\nGeraud: The shell will now exit.\nCamille:");
	ft_putendl("Please don't kill me one more time!\nFlavien: FFS");
	exit(1);
	signal++;
}
