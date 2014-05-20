/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 01:01:32 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 14:40:00 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		fill_ml_mp(t_mlmp *s, char *line)
{
	s->j = 0;
	s->tabl = ft_strsplit_spaces(line, ' ', 0);
	s->i = count_tab(s->tabl) - 1;
}

static char		*ml_mp(char *line, int *bol)
{
	t_mlmp		s;

	if (ft_strncmp(line, "cd -", 4))
		return (line);
	fill_ml_mp(&s, line);
	if (s.tabl[s.i][0] != '-')
	{
		s.j = 1;
		s.i--;
	}
	if (!(s.x = ft_strcmp(s.tabl[s.i], "-P")) || !ft_strcmp(s.tabl[s.i], "-L"))
	{
		if (!s.x)
			*bol = 1;
		ft_strdel(&line);
		line = ft_strdup(s.tabl[0]);
		if (s.j)
		{
			line = ft_strjoin(line, " ");
			line = ft_strjoin(line, s.tabl[count_tab(s.tabl) - 1]);
		}
		free_tab(&(s.tabl));
	}
	return (line);
}

char			*fn_appel(char *line, char **env, t_env *count, int *bol)
{
	line = ml_mp(line, bol);
	if (ft_strncmp(line, "cd ~/", 5) == 0)
	{
		if (count->home == -1)
		{
			ft_putendl("cd: line 4: cd: HOME not set");
			return (line);
		}
		line = ft_strsub(line, 4, ft_strlen(line));
		line = ft_strjoin(&env[count->home][5], line);
		line = ft_strjoin("cd ", line);
	}
	return (line);
}
