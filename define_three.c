/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:02:02 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 16:32:13 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		match_2(char *s1, char *s2)
{
	return (((*(s2 - 1) == '*' && *(s2 - 2) != '\\') &&\
	((*s2 == *s1 && *s2 == *(s1 + 1)) || *s2 == '?')\
	&& (*(s2 + 1) != *(s1 + 1) && *(s2 + 1) != '?')));
}

int		other_cd(t_in_other *e)
{
	return ((!ft_strcmp("cd", e->cmd) || !ft_strcmp("cd ~", e->cmd) ||\
	!ft_strcmp("cd --", e->cmd)));
}

int		why_chr(char *word)
{
	return ((ft_strchr(word, '/')) ? ft_strchr(word, '/') - word :\
	(int)ft_strlen(word));
}

int		ltv(t_ltverif v)
{
	return ((v.tabl[v.i][v.j] == ' ' && v.tabl[v.i][v.j + 1] &&\
	v.tabl[v.i][v.j + 1] == ' ' && !v.q));
}

int		path_maker(char **env, t_paths s)
{
	return ((ft_strchr(env[s.i], '/') && ft_strncmp("PWD", env[s.i], 3)\
	&& ft_strncmp("OLDPWD", env[s.i], 6)));
}
