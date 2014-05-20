/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 01:08:39 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 17:39:08 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			fill_why(t_why *e, char *ch)
{
	if (!ft_strchr(ch, '/'))
		ch = ft_strjoin("./", ch);
	e->path = pathing2(ch, &(e->i));
	e->pattern = ft_strsub(ch, e->i + 1, ft_strlen(ch));
}

static int			fill_complete(t_complete *s)
{
	s->env = get_env(NULL);
	s->count = get_count(NULL);
	s->begin = find_word2(g_glob.str, &(s->ch), g_glob.i);
	if (s->ch[0] == '$' || ft_strcmp(s->ch, "~") == 0)
		s->mot = vars_tab(s);
	else if (!first_word(s->begin, g_glob.str))
	{
		fill_why(&(s->e), s->ch);
		if ((s->directory = opendir(s->e.path)) == NULL)
			return (0);
		s->mot = find_match(s->directory, s->ch, s->e.path, 0);
	}
	else
		s->mot = whole_search(s);
	if (!s->mot || !s->mot[0])
		return (0);
	else if (!ft_strcmp(s->mot, s->ch))
		return (0);
	s->tableau = ft_strsplit(s->mot, ' ');
	s->fubs = g_glob.i;
	return (1);
}

static void			one_result(t_complete *s, t_term *term)
{
	s->tmp = ft_strdup(g_glob.str);
	s->len = ft_strlen(g_glob.str);
	ft_trans("cd");
	while (s->len >= 0)
	{
		ft_delete(term);
		s->len--;
	}
	s->len = ft_strlen(s->ch);
	g_glob.str = ft_strdup(s->tmp);
	ft_strdel(&(s->tmp));
	while (s->len)
	{
		g_glob.str = decale_word(g_glob.str, s->begin);
		s->len--;
	}
	g_glob.str = ft_strinjoin(g_glob.str, s->tableau[0], s->begin);
	s->fubs += ft_strlen(s->tableau[0]) - ft_strlen(s->ch);
}

void				ft_completion(t_term *term)
{
	t_complete		s;

	if (!fill_complete(&s))
		return ;
	if (count_tab(s.tableau) == 1)
		one_result(&s, term);
	else
	{
		ft_printf("\n%s\n", s.mot);
		get_prompt(s.env, s.count);
	}
	g_glob.i = ft_strlen(g_glob.str);
	ft_putstr(g_glob.str);
	while (g_glob.i > s.fubs)
	{
		ft_trans("le");
		g_glob.i--;
	}
	free_tab(&(s.tableau));
}
