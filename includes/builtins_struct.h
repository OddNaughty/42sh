/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 18:51:38 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/26 14:13:33 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_STRUCT_H
# define BUILTINS_STRUCT_H

t_builtins			g_bi_table[NBB] =
{
	{"cd", bi_cd},
	{"env", bi_env},
	{"exit", bi_exit},
	{"setenv", bi_setenv},
	{"unsetenv", bi_unsetenv},
	{"echo", bi_echo},
	{"read", bi_read},
	{"job", bi_job},
	{"fg", bi_fg},
	{"bg", bi_bg},
	{"unset", bi_unset},
	{"history", bi_history},
	{"export", bi_export},
	{"hash", bi_hash}
};

#endif
