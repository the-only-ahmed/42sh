/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parantheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 03:19:01 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 19:14:05 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		printing(int x)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (i < x)
	{
		len += ft_printf("crush> ");
		i++;
	}
	return (len);
}

static char		*ft_accolades(char *line, char *str)
{
	int			c_l;
	int			c_r;

	c_l = ft_occ_nb(line, '{');
	c_r = ft_occ_nb(line, '}');
	if (c_l > c_r)
	{
		while (c_l > c_r)
		{
			str = ft_termcaps(printing(c_l - c_r));
			c_l += ft_occ_nb(str, '{');
			c_r += (ft_occ_nb(str, '}') > 0) ? 1 : 0;
			line = ft_strjoin(line, str);
		}
		if (c_l < c_r)
			ft_printf("parse error near `}'\n");
	}
	else if (c_l < c_r)
	{
		ft_printf("parse error near `}'\n");
		return (NULL);
	}
	line = ft_and_or(line);
	return (line);
}

static char		*rac_line(int *p, char *line)
{
	char	*prompt;
	char	*str;

	if (p[0] - p[1] >= 2)
		prompt = ft_strdup("math>");
	else
		prompt = ft_strdup("subsh>");
	while (p[0] > p[1])
	{
		str = ft_termcaps(ft_printf("%s ", prompt));
		p[0] += ft_occ_nb(str, '(');
		p[1] += ft_occ_nb(str, ')');
		line = ft_strjoin(line, str);
	}
	ft_strdel(&prompt);
	if (p[0] < p[1])
	{
		ft_printf("parse error near `)'\n");
		return (NULL);
	}
	return (line);
}

char			*ft_parentheses(char *line, char *str)
{
	int			*p;

	p = (int*)malloc(sizeof(int) * 2);
	p[0] = ft_occ_nb(line, '(');
	p[1] = ft_occ_nb(line, ')');
	if (p[0] > p[1])
		line = rac_line(p, line);
	else if (p[0] < p[1])
	{
		ft_printf("parse error near `)'\n");
		return (NULL);
	}
	if (ft_strcmp(line, "[") == 0)
	{
		ft_printf("[: ']' expected\n");
		return (NULL);
	}
	if (ft_strchr(line, '[') && (ft_strchr(line, ']') || ft_strlen(line) > 1))
	{
		ft_printf("bad pattern %s\n", line);
		return (NULL);
	}
	line = ft_accolades(line, str);
	free(p);
	return (line);
}
