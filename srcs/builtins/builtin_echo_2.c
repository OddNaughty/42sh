/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mon_sbire <mon_sbire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 17:05:30 by mon_sbire          #+#    #+#             */
/*   Updated: 2014/03/25 19:32:33 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "builtins.h"

static int		ft_hexa_to_dec(char *str)
{
	int				result;
	int				index;

	result = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] >= '0' && str[index] <= '9')
			result += str[index] - '0';
		else if (str[index] >= 'a' && str[index] <= 'f')
			result += str[index] - 87;
		else if (str[index] >= 'A' && str[index] <= 'F')
			result += str[index] - 55;
		else
			return (-1);
		if (str[index + 1])
			result *= 8;
		index++;
	}
	return (result);
}

static void		ft_echo_octal(char *str, int index)
{
	char			*tmp;
	int				decimal;

	index++;
	tmp = (char *)malloc(sizeof(char) * 4);
	tmp[0] = str[index];
	tmp[1] = str[index + 1];
	tmp[2] = str[index + 2];
	tmp[3] = '\0';
	decimal = ft_hexa_to_dec(tmp);
	if (decimal == -1)
		ft_putstr(tmp);
	else
		ft_putchar(decimal);
	free(tmp);
}

static int		ft_sort_escaped(char c)
{
	if (c == 'a')
		ft_putchar(7);
	else if (c == 'b')
		ft_putchar(8);
	else if (c == 'f')
		ft_putchar('\f');
	else if (c == 'n')
		ft_putchar(10);
	else if (c == 'r')
		ft_putchar(13);
	else if (c == 't')
		ft_putchar(9);
	else if (c == 'v')
		ft_putchar(11);
	else
		return (0);
	return (1);
}

static int		ft_escaped(char *str)
{
	size_t			index;

	index = 0;
	while (str[index])
	{
		if (str[index] == 92)
		{
			index++;
			if (ft_sort_escaped(str[index]) == 0)
			{
				if (str[index] == '0')
				{
					ft_echo_octal(str, index);
					index += 3;
				}
				else if (str[index] == 'c')
					return (1);
				else
					ft_putchar(str[index]);
			}
			index++;
		}
		ft_putchar(str[index++]);
	}
	return (0);
}

void			ft_putstr_escaped(char **line, size_t start)
{
	while (line[start] != NULL)
	{
		if (ft_escaped(line[start]) == 1)
			return ;
		if (line[start + 1] != NULL)
			ft_putchar(' ');
		start++;
	}
}
