/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 13:55:45 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 17:08:15 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		chevron_son(t_tree **tree, char **env, char **cmd, t_env *count)
{
	if ((*tree)->left->cmd[0] == '<')
		(*tree) = (*tree)->left;
	if ((*tree)->cmd[0] == '<')
		ft_recup_tree(tree, env, count);
	else if (execve(cmd[0], cmd, env) < 0)
		ft_printf(": Execve Failed.\n");
}

void			chevron(t_tree **tree, char **env, t_env *count)
{
	int		father;
	int		file;
	int		chev;
	char	**cmd;

	chev = 1;
	if (!ft_strcmp((*tree)->cmd, ">"))
		chev = 0;
	(*tree)->left->done = 1;
	(*tree)->right->done = 1;
	cmd = fn_commande((*tree)->left->cmd, env, count);
	if (chev)
		file = open((*tree)->right->cmd, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		file = open((*tree)->right->cmd, O_RDWR | O_CREAT | O_TRUNC, 0666);
	father = fork();
	if (father > 0)
		wait(&father);
	else
	{
		dup2(file, 1);
		chevron_son(tree, env, cmd, count);
		close(file);
		exit(0);
	}
}

void			pipex2(t_tree **father, char **env, t_env *count)
{
	pid_t		pid;
	int			fd[2];

	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		exec_proc2(fd, &((*father)->right), env, count);
		exit(0);
	}
	if (pid == 0)
	{
		exec_proc1(&((*father)->left), fd, env, count);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void			pipex(t_tree **father, char **env, t_env *count)
{
	pid_t		f;
	t_tree		*tmp;

	tmp = (*father);
	while (tmp->father && priority(tmp->father->cmd) == 2)
	{
		tmp->father->left->done = 1;
		tmp->father->right->done = 1;
		tmp = tmp->father;
	}
	f = fork();
	(*father)->left->done = 1;
	(*father)->right->done = 1;
	if (f > 0)
		wait(0);
	if (f == 0)
	{
		pipex2(father, env, count);
		exit(0);
	}
}
