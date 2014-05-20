/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 06:41:37 by jyim              #+#    #+#             */
/*   Updated: 2014/03/26 10:51:11 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**tri_tab_ascii(char **env)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		while (env[i])
		{
			if (env[i + 1] && ft_strcmp(env[i], env[i + 1]) > 0)
			{
				flag = 0;
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			i++;
		}
		i = 0;
	}
	return (env);
}

char	**ft_strdup_tab(char **tab, int nb)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!tab)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (nb + count_tab(tab) + 1));
	while (tab[i])
	{
		tmp[i] = ft_strdup(tab[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int		search_exp(char *str, char **tab)
{
	int		i;
	int		len;
	int		size;
	char	**tmp;

	i = 0;
	size = count_tab(tab);
	if (ft_strchr(str, '='))
		len = ft_strchr(str, '=') - str;
	else
		len = ft_strlen(str);
	while (i < size)
	{
		tmp = ft_strsplit(tab[i], '=');
		if (!ft_strcmp(str, tmp[0]))
		{
			free_tab(&tmp);
			return (i);
		}
		free_tab(&tmp);
		i++;
	}
	return (-1);
}
