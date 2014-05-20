/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decale.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 03:41:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/23 04:30:49 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**decale_tab(char **tab, int i)
{
	while (tab[i])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	return (tab);
}

char	**decale_deb(char **tab, int pos, char *str)
{
	char	**tmp;
	int		n;
	int		i;
	int		j;

	n = count_tab(tab) + 1;
	tmp = (char**)malloc(sizeof(char*) * (n + 1));
	i = 0;
	j = 0;
	while (i < n)
	{
		if (i == pos)
		{
			tmp[i] = ft_strdup(str);
			i++;
		}
		tmp[i] = ft_strdup(tab[j]);
		i++;
		j++;
	}
	tmp[i] = NULL;
	free_tab(&tab);
	return (tmp);
}

char	*decale_word(char *s, int i)
{
	while (s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
	return (s);
}

char	*decale_word2(char *s, char c)
{
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			s = decale_word(s, i);
			i--;
		}
		i++;
	}
	return (s);
}

char	*decale_word3(char *s, int x)
{
	int		i;
	int		k;
	int		q;
	char	qt;

	i = 0;
	k = 0;
	q = 0;
	qt = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		q = verif_token(s[i], q, &qt);
		if (q != k && (x && qt != '`'))
			decale_word(s, i);
		k = q;
		i++;
	}
	return (s);
}
