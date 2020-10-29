/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfuncs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:45:46 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/26 14:53:13 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTFUNCS_H
# define PRINTFUNCS_H

# include "sh_termcaps.h"
/*
** PRINT FUNCS
*/
int		tputs_putchar(int c);
void	ft_putchar_cursor(char **line, char c, t_cursor *cursor);
void	ft_putstr_cursor(char **line, char *str, t_cursor *cursor);
void	ft_print_line(char **line, t_cursor *cursor);
void	insert_char(char **line, char c, t_cursor *cursor);
void	print_half_line(char *tm, t_cursor *cursor);
int		ft_putuser(int o_prompt);

#endif
