/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 01:21:28 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 18:05:23 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_others_fill(t_others *s, t_tree **tree, char **e)
{
	s->bol = (int *)malloc(sizeof(int));
	*(s->bol) = 0;
	s->cmd = (*tree)->cmd;
	s->bin = &((*tree)->bin);
	s->env = ft_strdup_tab(e, count_tab(e));
}

void			ft_argc(t_tree *tree, char **env, t_env *count)
{
	char		**cmd;
	t_others	s;

	ft_others_fill(&s, &tree, env);
	env = others(&s, count);
	if (!*(s.bol))
	{
		cmd = fn_commande(tree->cmd, env, count);
		cmd = ft_trait(cmd);
		ft_execve(cmd, env, &(tree->bin), tree->cmd);
	}
}

static void		ft_condition_tree(t_tree **tree, char **env, t_env *count)
{
	if (verif_bq((*tree)->cmd))
		(*tree)->cmd = bq((*tree)->cmd, env, count);
	if ((*tree)->cmd[0] == '(' && !(*tree)->done)
		skip_parent(tree, env, count);
	if ((*tree)->father && !ft_strcmp((*tree)->father->cmd, "|") &&
			!(*tree)->done)
		pipex(&((*tree)->father), env, count);
	if (work_chd(tree))
		chevron(&((*tree)->father), env, count);
	if (work_chl(tree))
		chevron_left(&((*tree)->father), env, count, 0);
}

static char		**ft_bol_tree(t_tree **tree, t_env *count, char **env)
{
	int			i;
	t_others	s;
	char		**c;

	i = 0;
	ft_others_fill(&s, tree, env);
	(*tree)->done = 1;
	env = others(&s, count);
	if (!*(s.bol))
	{
		while ((*tree)->cmd[i] && (*tree)->cmd[i] != ' ')
		{
			if ((*tree)->cmd[i] == '\\')
			{
				(*tree)->cmd = decale_word((*tree)->cmd, i);
				i--;
			}
			i++;
		}
		c = fn_commande((*tree)->cmd, env, count);
		c = ft_trait(c);
		ft_execve(c, env, &((*tree)->bin), (*tree)->cmd);
		free_tab(&c);
	}
	return (env);
}

char			**work_on(t_tree *tree, char **env, t_env *count)
{
	if (tree->left)
		work_on(tree->left, env, count);
	if (tree->right)
		work_on(tree->right, env, count);
	if (the_work(tree))
	{
		ft_condition_tree(&tree, env, count);
		if (!tree->done)
		{
			env = ft_bol_tree(&tree, count, env);
			if (tree->father && priority(tree->father->cmd) == 3)
				tree->father->bin = tree->bin;
			if (tree->father && priority(tree->father->cmd) == 3)
				binaire_exec(&(tree->father));
		}
	}
	if (!ft_strcmp(tree->cmd, THE_CREED))
	{
		tree->bol = 0;
		tree->cmd = ft_strdup(tree->right->cmd);
	}
	return (env);
}
