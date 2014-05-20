/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occurence.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 15:23:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 17:05:57 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_occ_nb(const char *str, char c)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && back_line((char*)str, i))
			x++;
		i++;
	}
	return (x);
}

int		nb_word_occ(char *s1, char *s2)
{
	int		i;
	int		j;
	int		occ;

	i = 0;
	j = 0;
	occ = 0;
	while (s2[i])
	{
		if (s2[i] == s1[j])
			j++;
		else
			j = 0;
		if (!s1[j])
			occ++;
		i++;
	}
	return (occ);
}
