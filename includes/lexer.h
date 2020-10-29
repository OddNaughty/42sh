/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:06:43 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/26 15:15:32 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define NO -2
# define NBR_TOK 10

typedef struct		s_lexer
{
	char			*value;
	int				token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

enum				e_token
{
	COMA = 1,
	AND = 2,
	OR = 3,
	PIPE = 4,
	OUT = 5,
	AOUT = 6,
	AIN = 7,
	IN = 8,
	CMD = 9,
	ERROR = 10
};

/*
**List prototype: lstlex.c
*/
int					addtolex(t_lexer **lexer, char *value, int token);
void				printlex(t_lexer **lexed);
void				lex_freeone(t_lexer *tmp);
int					counttoken(t_lexer **lexer, int token);

/*
**Lexing: lexing.c
*/
t_lexer				*lexit(char *str);
void				printlex(t_lexer **lexed);
int					addcmd(t_lexer **lexer, char *str, int i);

/*
** Prototype: checktoken.c && checktoken_2.c
*/
int					is_pipe(t_lexer **lexer, char **str, int *index);
int					is_out(t_lexer **lexer, char **str, int *index);
int					is_aout(t_lexer **lexer, char **str, int *index);
int					is_in(t_lexer **lexer, char **str, int *index);
int					is_ain(t_lexer **lexer, char **str, int *index);
int					is_and(t_lexer **lexer, char **str, int *index);
int					is_or(t_lexer **lexer, char **str, int *index);
int					is_coma(t_lexer **lexer, char **str, int *index);

/*
**srcs/: error.c && free.c
*/
int					syntax_error(t_lexer *lexer);
void				free_lexer(t_lexer **lex);

#endif
