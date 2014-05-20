/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 13:45:54 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 19:07:41 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		end_p(char *line)
{
	if (line[ft_strlen(line) - 1] == '&' && line[ft_strlen(line) - 2] == '&')
		return (3);
	if (line[ft_strlen(line) - 1] == '|')
	{
		if (line[ft_strlen(line) - 2] == '|')
			return (2);
		return (1);
	}
	return (0);
}

static void		ft_and_or2(char *line, t_miss *m)
{
	if (m->p == 3)
	{
		m->i = 0;
		m->a = nb_word_occ("&&", line);
	}
	else if (m->p == 2)
	{
		m->i = 0;
		m->c = nb_word_occ("||", line);
	}
	else
		m->i = ft_occ_nb(line, '|') - 2 * m->c;
}

static char		*ft_and_or3(char *line, t_miss *m)
{
	int		len;

	m->j = m->c;
	len = 0;
	while (m->j)
	{
		len += ft_printf("cmdor");
		m->j--;
		if (m->j || (!m->j && m->i))
			len += ft_printf(" ");
	}
	m->j = m->i;
	while (m->j)
	{
		len += ft_printf("pipe");
		m->j--;
		if (m->j)
			len += ft_printf(" ");
	}
	len += ft_printf("> ");
	m->str = ft_termcaps(len);
	line = ft_strjoin(line, m->str);
	return (line);
}

char			*ft_and_or(char *line)
{
	t_miss		m;

	m.c = 0;
	if (ft_strchr(line, '|') == line || ft_strchr(line, '&') == line)
		return (line);
	while ((m.p = end_p(line)))
	{
		ft_and_or2(line, &m);
		m.j = m.a;
		while (m.j)
		{
			ft_printf("cmdand");
			m.j--;
			if (m.j || (!m.j && m.i) || (!m.j && m.c))
				ft_putchar(' ');
		}
		line = ft_and_or3(line, &m);
	}
	return (line);
}
