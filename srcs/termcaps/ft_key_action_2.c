/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 12:47:24 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 18:29:00 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_termcaps.h"
#include "libft.h"

int				key_is_print(char **line, t_cursor *cursor, char c)
{
	if (c == '\t' || c == '\n')
		return (0);
	if (cursor->strlen < BUFF_SIZE && cursor->string == cursor->strlen)
	{
		(*line)[cursor->string] = c;
		ft_putchar_cursor(line, c, cursor);
		return (0);
	}
	else if (cursor->strlen < BUFF_SIZE && cursor)
	{
		insert_char(line, c, cursor);
	}
	return (1);
}

int				key_is_alt_plus_left(char **line, t_cursor *cursor)
{
	size_t			i;

	i = cursor->string;
	if (i > 0)
		i--;
	while (i != 0 && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i--;
	while (i != 0 && ((*line)[i - 1] != ' ' && (*line)[i - 1] != '\t'))
		i--;
	if (i == 0 && ((*line)[i] == ' ' || (*line)[i] == '\t'))
	{
		while ((*line)[i] == ' ' || (*line)[i] == '\t')
			i++;
	}
	while (key_is_left(line, cursor) != 1)
		;
	while (cursor->string < i)
		key_is_right(line, cursor);
	return (0);
}

static size_t	key_is_alt_plus_right_2(char **line, size_t i)
{
	i--;
	while (i != 0 && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i--;
	return (i);
}

int				key_is_alt_plus_right(char **line, t_cursor *cursor)
{
	size_t			i;
	size_t			len;

	i = cursor->string;
	len = ft_strlen(*line);
	if (i < ft_strlen(*line))
		i++;
	while (i < len && ((*line)[i] != ' ' && (*line)[i] != '\t'))
		i++;
	while (i < len && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	while (i < len && ((*line)[i - 1] != ' ' && (*line)[i - 1] != '\t'))
		i++;
	if (i == len)
	{
		i = key_is_alt_plus_right_2(line, i);
		while (i != 0 && ((*line)[i - 1] != ' ' && (*line)[i - 1] != '\t'))
			i--;
	}
	while (key_is_left(line, cursor) != 1)
		;
	while (cursor->string < i)
		key_is_right(line, cursor);
	return (0);
}
