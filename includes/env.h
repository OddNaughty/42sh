/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 21:35:43 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/26 14:15:29 by mon_sbire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
**File: env_tools1.c
*/
char	**env_copyenv(void);
char	*ft_getenv(const char *name, char **env);
int		env_findline(char *name, char **env);
int		env_reallocone(char ***env, char *str);
int		env_minusone(char ***env, char *str);
/*
**File: env_tools2.c
*/
int		env_changeline(char ***env, char **line, int i);
char	**save_env(char **new_env, int rw);
#endif
