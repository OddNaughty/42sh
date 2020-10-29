/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_tab.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 12:37:50 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/26 15:03:10 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_TAB_H
# define TERMCAPS_TAB_H

t_funct			g_functab[CMD_NBR] =
{
	{LEFT_KEY, key_is_left},
	{RIGHT_KEY, key_is_right},
	{HOME_KEY, key_is_home},
	{END_KEY, key_is_end},
	{ALT_PLUS_LEFT_KEY, key_is_alt_plus_left},
	{ALT_PLUS_RIGHT_KEY, key_is_alt_plus_right},
	{ALT_PLUS_UP_KEY, key_is_alt_plus_up},
	{ALT_PLUS_DOWN_KEY, key_is_alt_plus_down},
	{BACKSPACE_KEY, key_is_backspace},
	{DEL_KEY, key_is_del},
	{CTRL_PLUS_L_KEY, key_is_ctrl_plus_l},
	{UP_KEY, key_is_up},
	{DOWN_KEY, key_is_down}
};

#endif
