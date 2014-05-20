/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 02:55:00 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 18:40:43 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**realloc_norme(char *s2, int *i, int *i2, char **tmp)
{
	(*i2)++;
	tmp[*i2] = ft_strdup("|");
	(*i2)++;
	tmp[*i2] = s2;
	(*i2)++;
	(*i)++;
	return (tmp);
}

static char		**realloc_tab(char **tab, int index, char *s, char *s2)
{
	int		i;
	int		i2;
	char	**tmp;

	if (!tab)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (count_tab(tab) + 3));
	i = 0;
	i2 = 0;
	while (tab[i])
	{
		if (i == index)
		{
			tmp[i2] = s;
			tmp = realloc_norme(s2, &i, &i2, tmp);
		}
		else
			tmp[i2++] = tab[i++];
	}
	tmp[i2] = NULL;
	free(tab);
	return (tmp);
}

char			**adds(char **tab)
{
	int		i;
	int		x;
	char	*s1;
	char	*s2;

	i = 0;
	while (tab[i])
	{
		if (i && !ft_strcmp(tab[i - 1], "<"))
		{
			if (ft_occ_nb(tab[i], ' '))
			{
				x = ft_strchr(tab[i], ' ') - tab[i];
				s1 = ft_strsub(tab[i], 0, x);
				s2 = ft_strsub(tab[i], x + 1, ft_strlen(tab[i]) - x);
				tab = realloc_tab(tab, i, s1, s2);
			}
		}
		i++;
	}
	return (tab);
}
