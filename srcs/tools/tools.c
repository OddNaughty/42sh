/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffondane <ffondane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 12:36:19 by ffondane          #+#    #+#             */
/*   Updated: 2014/03/25 13:33:13 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <sys/stat.h>
#include "libft.h"
int				is_directory(char *path)
{
	struct stat	sb;

	stat(path, &sb);
	if (S_ISDIR(sb.st_mode))
		return (0);
	return (1);
}

int				is_file(char *path)
{
	struct stat sb;

	stat(path, &sb);
	if (S_ISREG(sb.st_mode))
		return (0);
	return (1);
}
