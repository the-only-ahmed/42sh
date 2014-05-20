/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 09:43:42 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 15:20:06 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_proc1(t_tree **left, int *fd, char **env, t_env *count)
{
	char	**cmd;

	dup2(fd[1], 1);
	close(fd[0]);
	if ((*left)->cmd[0] == '<')
	{
		(*left)->father->done = 1;
		ft_recup_tree(left, env, count);
	}
	else
	{
		cmd = fn_commande((*left)->cmd, env, count);
		ft_execve(cmd, env, &((*left)->bin), (*left)->cmd);
	}
}

void	exec_proc2(int *fd, t_tree **right, char **env, t_env *count)
{
	char	**cmd;

	dup2(fd[0], 0);
	close(fd[1]);
	cmd = fn_commande((*right)->cmd, env, count);
	if (pipe_right_chd(right))
	{
		(*right)->father->father->left->cmd = ft_strdup((*right)->cmd);
		chevron(&((*right)->father->father), env, count);
		exit(0);
	}
	if ((*right)->father->father &&
		!ft_strcmp((*right)->father->father->cmd, "|"))
	{
		(*right)->father->father->left->cmd = ft_strdup((*right)->cmd);
		pipex2(&((*right)->father->father), env, count);
		exit(0);
	}
	ft_execve(cmd, env, &((*right)->bin), (*right)->cmd);
	exit(0);
}

void	ft_recup_tree(t_tree **tree, char **env, t_env *count)
{
	if (!(*tree) || !(*tree)->left || ((*tree)->cmd[0] != '<' &&
			ft_strcmp((*tree)->cmd, THE_CREED)))
		return ;
	else
	{
		ft_recup_tree(&((*tree)->left), env, count);
		ft_putendl_fd((*tree)->cmd, 2);
		if (ft_strcmp((*tree)->cmd, THE_CREED) == 0)
		{
			(*tree)->bol = 0;
			(*tree)->cmd = ft_strdup((*tree)->right->cmd);
		}
		else
			chevron_left(tree, env, count, 1);
	}
}
