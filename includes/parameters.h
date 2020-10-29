/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 20:57:40 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/26 14:31:02 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H
# include "libft.h"
# include <stdlib.h>
/*
** Ici seront nos premiers parameters a l'execution du 42sh (srcs/parameters)
*/

/*
** info.c
*/
void		parameters(t_shell *shell, char **argv);
void		version(t_shell *shell);
void		help(t_shell *shell);

#endif
