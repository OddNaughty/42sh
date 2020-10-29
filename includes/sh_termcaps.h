/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_termcaps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 16:33:02 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/27 14:48:26 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TERMCAPS_H
# define SH_TERMCAPS_H

# define CMD_NBR 13
# define BUFF_SIZE 4096

# include <curses.h>
# include <term.h>
# include "sh42.h"

typedef struct termios	t_termios;

enum					e_key
{
	RIGHT_KEY = 4414235,
	LEFT_KEY = 4479771,
	UP_KEY = 4283163,
	DOWN_KEY = 4348699,
	BACKSPACE_KEY = 127,
	DEL_KEY = 2117294875,
	RETURN_KEY = 10,
	CTRL_PLUS_L_KEY = 12,
	HOME_KEY = 4741915,
	END_KEY = 4610843,
	ALT_PLUS_LEFT_KEY = 1146821403,
	ALT_PLUS_RIGHT_KEY = 1130044187,
	ALT_PLUS_UP_KEY = 1096489755,
	ALT_PLUS_DOWN_KEY = 1113266971
};

typedef struct			s_llist
{
	char				*line;
	size_t				position;
	struct s_llist		*prev;
	struct s_llist		*next;
}						t_llist;

typedef struct			s_histo
{
	int					fd;
	char				*current_cmd;
	char				*path_cmd;
	size_t				position;
	size_t				size;
	t_llist				*initial;
	t_llist				*llist;
}						t_histo;

typedef struct			s_cursor
{
	size_t				string;
	size_t				lprompt;
	size_t				strlen;
	char				*quote;
	t_histo				*histo;
}						t_cursor;

typedef struct			s_funct
{
	size_t				key_value;
	int					(*process)(char **line, t_cursor *cursor);
}						t_funct;

/*
** READ INPUTS
*/
void					read_input(char **line, int len);
int						input_line(char **line);

/*
** KEYS
*/
int						key_is_left(char **line, t_cursor *cursor);
int						key_is_right(char **line, t_cursor *cursor);
int						key_is_print(char **line, t_cursor *cursor, char c);
int						key_is_home(char **line, t_cursor *cursor);
int						key_is_end(char **line, t_cursor *cursor);
int						key_is_alt_plus_left(char **line, t_cursor *cursor);
int						key_is_alt_plus_right(char **line, t_cursor *cursor);
int						key_is_alt_plus_up(char **line, t_cursor *cursor);
int						key_is_alt_plus_down(char **line, t_cursor *cursor);
int						key_is_ctrl_plus_l(char **line, t_cursor *cursor);
int						key_is_backspace(char **line, t_cursor *cursor);
int						key_is_delete(char **line, t_cursor *cursor);
int						key_is_del(char **line, t_cursor *cursor);
int						key_is_return(char **line, t_cursor *cursor);
t_histo					*save_history(t_histo *histo, int rw);
void					open_history(void);
void					free_histo(void);
void					search_quote(char *s, t_cursor *cursor);
void					fill_histo_llist(t_histo *histo, char *line);
int						key_is_up(char **line, t_cursor *cursor);
int						key_is_down(char **line, t_cursor *cursor);

/*
** PRINT FUNCS
*/
int						tputs_putchar(int c);
void					ft_putchar_cursor(char **line, char ca, t_cursor *c);
void					ft_putstr_cursor(char **line, char *str, t_cursor *c);
void					ft_print_line(char **line, t_cursor *cursor);
void					insert_char(char **line, char c, t_cursor *cursor);
void					print_half_line(char *tm, t_cursor *cursor);
int						ft_putuser(void);

/*
** DEPLACEMENT
*/
int						is_right(t_cursor *cursor);
int						is_left(t_cursor *cursor);

/*
** TERMIOS
*/
int						set_shell(t_shell *info);
int						restore_shell(void);
void					set_termios(void);
void					restore_termios(void);

/*
** SIGNALS
*/
void					set_signal_cmd(void);
char					**save_line_ptr(char **line, int rw);
t_cursor				*save_cursor_ptr(t_cursor *cursor, int rw);
void					ft_resize_signal(int signal);
void					ft_handle_signal(int signal);
void					handle_seg(int signal);
void					ft_handle_signal2(int signal);
void					ft_handle_critic(int signal);
void					signal_init(void);
t_shell					*save_t_shell(t_shell *info, int rw);
t_termios				save_term(struct termios termios, int rw);

#endif
