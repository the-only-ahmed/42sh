/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 02:36:30 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 21:30:31 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			**change_tab(char **tab, int pos)
{
	while (tab[pos + 1])
	{
		tab[pos] = ft_strdup(tab[pos + 1]);
		pos++;
	}
	tab[pos] = NULL;
	return (tab);
}

t_l				*add_end(t_l *list, char **tab)
{
	t_l		*tmp;
	t_l		*tmp2;

	tmp2 = (t_l *)malloc(sizeof(t_l));
	tmp2->next = NULL;
	tmp2->array = tab;
	tmp2->prev = NULL;
	if (list == NULL)
		return (tmp2);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tmp2;
	tmp2->prev = tmp;
	return (list);
}

char			**splits(char **tab, int start, int end)
{
	int		i;
	char	**mat;

	mat = (char**)malloc(sizeof(char*) * (end - start + 2));
	i = 0;
	while (start <= end)
	{
		mat[i] = ft_strdup(tab[start]);
		i++;
		start++;
	}
	mat[i] = NULL;
	return (mat);
}

char			**subs(char **tab)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], ""))
		{
			j = i;
			while (tab[j])
			{
				tab[j] = tab[j + 1];
				j++;
			}
		}
		i++;
	}
	return (tab);
}
