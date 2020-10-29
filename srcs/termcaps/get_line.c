/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 14:01:16 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 17:23:44 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"
#include "colors.h"
#include "sh42.h"
#include "env.h"

int				ft_putuser(void)
{
	t_shell				*info;
	char				*home;
	char				*pwd;
	unsigned int		len;

	info = save_t_shell(NULL, 0);
	home = ft_getenv("HOME", info->env);
	pwd = ft_getenv("PWD", info->env);
	len = ft_strlen(home);
	ft_putstr((info->cmdret ? "\033[1;31m[" : "\033[1;36m["));
	if (ft_strlen(pwd) < len)
	{
		len = ft_strlen(pwd);
		ft_putstr(pwd);
	}
	else
	{
		ft_putstr(pwd + len);
		len = ft_strlen(pwd + len);
	}
	ft_putstr("]> \033[0m");
	free(home);
	free(pwd);
	return (len + 4);
}

int				input_line(char **line)
{
	int				len;

	len = ft_putuser();
	*line = ft_strnew(BUFF_SIZE);
	read_input(line, len);
	return (SUCCESS);
}
