/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_finder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 01:05:41 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 17:39:41 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		path_filler(t_paths *s, char **env)
{
	s->i = -1;
	s->x = 0;
	s->mat = (char **)malloc(sizeof(char*) * (count_tab(env) + 1));
}

static char		**ft_make_paths(char **env)
{
	t_paths		s;

	path_filler(&s, env);
	while (env[++s.i])
	{
		if (path_maker(env, s))
		{
			s.str = ft_strchr(env[s.i], '=') + 1;
			s.tabl = ft_strsplit(s.str, ':');
			s.j = -1;
			while (s.tabl[++s.j])
			{
				s.mat[s.x] = ft_strdup(s.tabl[s.j]);
				if (s.tabl[s.j] && !ft_strchr(s.tabl[s.j], '/'))
				{
					s.mat[s.x] = ft_strjoin(s.mat[s.x], ":");
					s.mat[s.x] = ft_strjoin(s.mat[s.x], s.tabl[s.j]);
					s.j++;
				}
				s.x++;
			}
			free_tab(&(s.tabl));
		}
	}
	return (s.mat);
}

static char		*delete_repeated(char *mot)
{
	int		i;
	char	**tab;
	char	*str;

	tab = ft_strsplit(mot, ' ');
	i = -1;
	while (tab[++i])
	{
		if (search_exp(tab[i], tab) != i)
		{
			decale_tab(tab, i);
			i--;
		}
	}
	ft_strdel(&mot);
	str = ft_all_strjoin(tab);
	free_tab(&tab);
	return (str);
}

char			*whole_search(t_complete *s)
{
	int		i;
	char	**paths;

	i = -1;
	if (!is_word(g_glob.str))
		return (NULL);
	s->mot = ft_strnew(0);
	paths = ft_make_paths(s->env);
	while (paths[++i])
	{
		if ((s->directory = opendir(paths[i])) == NULL)
			continue ;
		if (i)
			s->mot = ft_strjoin(s->mot, " ");
		s->mot = ft_strjoin(s->mot, find_match(s->directory, s->ch, NULL, 0));
	}
	s->mot = delete_repeated(s->mot);
	return (s->mot);
}
