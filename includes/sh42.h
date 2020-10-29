/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:28:58 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 16:50:33 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SH42_H
# define SH42_H

# define SUCCESS 0
# define FAILURE -1
# define BINNAME "42sh"
# define VERSION "0.1"

/*
** Structure
*/
typedef struct		s_hlist
{
	int				code;
	int				count;
	struct s_hlist	*next;
}					t_hlist;

typedef struct		s_shell
{
	int				cmdret;
	char			**cmd;
	char			*str;
	char			**env;
	char			**htab;
	t_hlist			*hlist;
}					t_shell;

/*
**42sh/srcs/cmd/: Relative to command executions.
*/
int					cmd_execute(t_shell *shell, char **env);
int					cmd_executeit(char **env, t_shell *shell, char *path);
char				*cmd_searchpath(char *cmd, char **env);
int					hash_check(char *cmd, char **htab, int *code);
int					hash_cmdtoint(char *cmd);
void				hash_add(int code, t_shell *shell);
void				hash_init(t_shell *info, int flag);

/*
**srcs/: error.c
*/
void				*err_malloc(char *str, char *varname);
int					failure_error(char *str);

#endif
