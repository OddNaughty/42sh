/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 13:36:06 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 15:54:11 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"
#include "env.h"

t_shell			*save_t_shell(t_shell *info, int rw)
{
	static t_shell			*info_save;

	if (rw == 1)
		info_save = info;
	return (info_save);
}

int				restore_shell(void)
{
	t_histo					*histo;

	histo = save_history(NULL, 0);
	close(histo->fd);
	restore_termios();
	return (0);
}

static int		histo_fd(t_histo *histo)
{
	t_shell					*shell;
	char					*path;
	int						fd;

	fd = -1;
	shell = save_t_shell(NULL, 0);
	path = ft_getenv("HOME", shell->env);
	if (path == NULL)
		return (-1);
	histo->path_cmd = ft_strjoin(path, "/.42sh_history");
	free(path);
	if (histo->path_cmd == NULL)
		return (-1);
	fd = open(histo->path_cmd, O_CREAT | O_RDWR, 0777);
	return (fd);
}

void			open_history(void)
{
	t_histo					*histo;
	char					*line;

	histo = malloc(sizeof(t_histo));
	histo->llist = NULL;
	histo->fd = histo_fd(histo);
	histo->initial = NULL;
	histo->position = 0;
	histo->size = 0;
	if (histo->fd == -1)
	{
		ft_putendl("Can't open history, commands will not be saved properly.");
		save_history(histo, 1);
		return ;
	}
	while (get_next_line(histo->fd, &line))
	{
		fill_histo_llist(histo, line);
		free(line);
	}
	save_history(histo, 1);
}

int				set_shell(t_shell *info)
{
	struct termios			term;
	char					*term_name;

	hash_init(info, 0);
	if ((term_name = getenv("TERM")) == NULL)
	{
		ft_putendl_fd("Cant work without environement.", 2);
		exit(-1);
	}
	if ((tgetent(NULL, term_name)) == ERR)
		exit(-1);
	if (tcgetattr(0, &term) == -1)
		exit(-1);
	save_term(term, 1);
	save_t_shell(info, 1);
	open_history();
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		exit(-1);
	return (0);
}
