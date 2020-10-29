/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 15:56:20 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 15:32:15 by elazarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# define NBB 14
# define MAXPATHLEN 200
# include "sh42.h"
# include <string.h>

/*
** Structure table des builtins
*/

typedef struct			s_builtins
{
	char				*cmd;
	int					(*f_bi) (t_shell *shell);
}						t_builtins;

/*
** Builtins obligatoire : builtins.c & builtins_extra.c
*/
int						is_builtins(t_shell *shell, char *cc, int fg);
int						bi_env(t_shell *shell);
int						bi_exit(t_shell *shell);
int						bi_setenv(t_shell *shell);
int						bi_unsetenv(t_shell *shell);
int						bi_echo(t_shell *shell);

/*
** Builtins bonus : builtins_bonus.c & builtins_bonus_extra.c
*/
int						bi_read(t_shell *shell);
int						bi_job(t_shell *shell);
int						bi_fg(t_shell *shell);
int						bi_bg(t_shell *shell);
int						bi_unset(t_shell *shell);
int						bi_export(t_shell *shell);
int						bi_hash(t_shell *shell);

/*
** Builtin echo : builtin_echo_1.c & builtin_echo_2.c
*/
int						bi_echo(t_shell *shell);
void					ft_putstr_escaped(char **line, size_t start);

/*
** Builtin history : bi_history_1.c
*/

int						bi_history(t_shell *shell);

/*
** Builtins tools : builtins_tools.c
*/
int						bi_error(t_shell *shell, char *msg);
void					ft_free3char(char **one, char **two, char **three);

/*
** Builtins cd : bi_cd.c & bi_cd2.c
*/
int						bi_cd(t_shell *shell);
int						is_home(t_shell *shell, int pos);
int						is_homepath(t_shell *shell, int pos);
int						is_opts(t_shell *shell);
int						is_back(t_shell *shell, int pos);
int						do_fromhome_chdir(t_shell *shell, int opts, int pos);
int						do_special_chdir(t_shell *shell, int opts, int to);
int						do_chdir(t_shell *shell, char *path, int opts);

/*
** Builtins hash : bi_hash.c & bi_hash2.c
*/
void					hash_error(char *arg, int fg);
int						hash_options(char **cmd, int fg);

/*
** Builtins setenv: bi_setenv.c
*/
int						bi_dochanges(t_shell *shell, int i);
int						bi_reallocone(char ***env, char *str);
int						bi_dosetenv(char ***env, char *key, char *value);

#endif
