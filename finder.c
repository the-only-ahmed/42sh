/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 21:00:00 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 21:18:15 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				find_word3(char *str, char **ch, char c, char d)
{
	int		b;
	int		e;
	int		x;

	b = ft_strchr(str, c) - str;
	e = b;
	x = b;
	if (!(ft_strchr(str, c)))
		return (-1);
	while (b >= 0)
	{
		if (str[b] == ' ' || str[b] == '\t' || (str[b] == d && b != x))
			break ;
		b--;
	}
	b++;
	while (str[e])
	{
		if (str[e] == ' ' || str[e] == '\t' || (str[e] == d && e != x))
			break ;
		e++;
	}
	e--;
	*ch = ft_strsub(str, b, e - b + 1);
	return (b);
}

int				find_word2(char *str, char **ch, int c)
{
	int		b;
	int		e;

	while (c && str[c] == ' ')
		c--;
	b = c;
	e = b;
	while (b >= 0)
	{
		if (str[b] == ' ' || str[b] == '\t')
			break ;
		b--;
	}
	b++;
	while (str[e])
	{
		if (str[e] == ' ' || str[e] == '\t')
			break ;
		e++;
	}
	e--;
	*ch = ft_strsub(str, b, e - b + 1);
	return (b);
}

int				find_word(char *str, char **ch, char c)
{
	int		b;
	int		e;

	b = ft_strchr(str, c) - str;
	e = b;
	if (!(ft_strchr(str, c)))
		return (-1);
	while (b >= 0)
	{
		if (str[b] == ' ' || str[b] == '\t')
			break ;
		b--;
	}
	b++;
	while (str[e])
	{
		if (str[e] == ' ' || str[e] == '\t')
			break ;
		e++;
	}
	e--;
	*ch = ft_strsub(str, b, e - b + 1);
	return (b);
}

int				first_word(int b, char *str)
{
	int		i;

	i = 0;
	while (i < b)
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
