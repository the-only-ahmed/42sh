/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sous_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 06:07:50 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/19 15:11:33 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**tab_dup(char **env)
{
	int		i;
	char	**tab;

	i = 0;
	tab = (char**)malloc(sizeof(char*) * (count_tab(env) + 1));
	while (env[i])
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	skip_parent(t_tree **father, char **env, t_env *count)
{
	t_tree	*tree;
	char	**tmp;
	pid_t	pid;

	(*father)->cmd = decale_word((*father)->cmd, 0);
	(*father)->cmd[ft_strlen((*father)->cmd) - 1] = '\0';
	(*father)->done = 1;
	tmp = tab_dup(env);
	pid = fork();
	if (pid)
		wait(0);
	if (!pid)
	{
		tree = parser((*father)->cmd);
		work_on(tree, tmp, count);
		exit(0);
	}
}
