/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 20:20:02 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/26 16:44:36 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "sh42.h"

# define MAX_PIPES 60

typedef struct		s_tree
{
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_tree	*parent;
	char			*value;
	int				token;
}					t_tree;

typedef struct		s_state
{
	int				out;
	int				in;
	int				pipes;
}					t_state;

/*
**File: parsing.c
*/
t_tree				*parseit(t_lexer **lexer);
t_tree				*initnode(int token, t_tree *father);
t_tree				*buildtree(t_lexer **lexer, int token, t_tree *father);
void				printtree(t_tree *tree, int i);

/*
**File: check1.c
*/
int					checksyntax(t_lexer **lexer);

/*
**File: check2.c
*/
int					check_redir(t_state *state, t_lexer *lexer);

/*
**File: check3.c
*/
void				check_permission(t_lexer *lexer);

/*
**File: ../cmd/dotree.c && redirn
*/
int					dotree(t_tree *parser, t_shell **shell);
int					redir_coma(t_tree *parser, t_shell **shell);
int					redir_and(t_tree *parser, t_shell **shell);
int					redir_or(t_tree *parser, t_shell **shell);
int					redir_pipe(t_tree *parser, t_shell **shell);
int					redir_ain(t_tree *parser, t_shell **shell);
int					redir_out(t_tree *parser, t_shell **shell);
int					redir_aout(t_tree *parser, t_shell **shell);
int					redir_in(t_tree *parser, t_shell **shell);
int					redir_cmd(t_tree *parser, t_shell **shell);
int					redir_error(t_tree *parser, t_shell **shell);

/*
**File: ../free.c
*/
void				free_parser(t_tree **parser);

#endif
