/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 14:29:25 by jyim              #+#    #+#             */
/*   Updated: 2014/03/26 10:51:38 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**rel_exp(char **tab, int *pos, char **temp, char *arg)
{
	if (!ft_strcmp(temp[0], "_"))
	{
		ft_putendl("42sh : read-only variable: _");
		tab[(*pos)++] = ft_strdup(THE_CREED);
	}
	else
		tab[(*pos)++] = ft_strdup(arg);
	return (tab);
}

static char		**rel_exp_loop(char *arg, char **tab, int *pos)
{
	char	**temp;
	int		p;

	temp = ft_strsplit(arg, '=');
	if ((p = search_exp(temp[0], tab)) != -1 && ft_strcmp(temp[0], "_"))
	{
		ft_strdel(&tab[p]);
		if (temp[1])
		{
			tab[p] = ft_strjoin(temp[0], "=");
			tab[p] = ft_strjoin(tab[p], temp[1]);
		}
		else
			tab[p] = ft_strdup(temp[0]);
		return (tab);
	}
	tab = rel_exp(tab, pos, temp, arg);
	free_tab(&temp);
	return (tab);
}

char			**real_exp(char **env, char **arg)
{
	char	**tab;
	char	*tmp;
	int		pos;
	int		i;

	pos = search_exp("_", env);
	tab = ft_strdup_tab(env, count_tab(arg) + 1);
	tmp = ft_strdup(tab[pos]);
	i = -1;
	while (arg[++i])
		tab = rel_exp_loop(arg[i], tab, &pos);
	tab[pos++] = tmp;
	tab[pos] = NULL;
	free_tab(&env);
	return (tab);
}

char			**ft_exports(char **env, char **tab)
{
	char		**export;
	int			p;

	p = 0;
	if (tab[1] && ft_strcmp(tab[1], "-p") == 0)
		p = 1;
	export = ft_strdup_tab(env, 1);
	export = tri_tab_ascii(export);
	if (!tab[1] || (tab[1] && p && !tab[2]))
	{
		if (p)
			aff_tab_export(export, NULL);
		else
			aff_tab_e(export);
	}
	else if (p && count_tab(export) > 2)
		aff_tab_export(export, &tab[2]);
	else
		env = real_exp(env, &tab[1]);
	free_tab(&export);
	return (env);
}
