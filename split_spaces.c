/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 02:53:01 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 15:55:33 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_count_split(char const *s, char c)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	while (s[i2] != '\0')
	{
		if (s[i2] == c)
			i2++;
		if (s[i2] != c)
		{
			i2++;
			i++;
		}
	}
	return (i);
}

static char		**fill_splaces(char *str, t_dlspaces *s, char c)
{
	s->i = 0;
	s->i2 = 0;
	s->q = 0;
	s->qt = 0;
	if (str == NULL)
		return (NULL);
	s->tmp = (char **)malloc(sizeof(char *) * (ft_count_split(str, c) + 1));
	return (s->tmp);
}

char			**ft_strsplit_spaces(char const *str, char c, int x)
{
	t_dlspaces		s;

	if (!(s.tmp = fill_splaces((char *)str, &s, c)))
		return (NULL);
	while (str[s.i] != '\0')
	{
		s.cnt = 0;
		s.q = verif_token(str[s.i], s.q, &(s.qt));
		while (split_sp_tok(s, str, c))
		{
			s.i++;
			s.q = verif_token(str[s.i], s.q, &(s.qt));
		}
		while (split_spaces(s, str, c))
		{
			s.cnt++;
			s.q = verif_token(str[s.i + s.cnt], s.q, &(s.qt));
		}
		s.tmp[s.i2] = ft_strsub(str, s.i, s.cnt);
		s.i = s.cnt + s.i;
		s.tmp[s.i2] = decale_word3(s.tmp[s.i2], x);
		s.i2++;
	}
	s.tmp[s.i2] = NULL;
	return (s.tmp);
}
