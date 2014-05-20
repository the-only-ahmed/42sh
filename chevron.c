/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 23:55:01 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/26 08:29:17 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				fn_chev_2(t_tree *tree, char **env, t_env *count)
{
	int		father;
	int		file;
	char	**cmd;

	cmd = fn_commande(tree->left->cmd, env, count);
	file = open(tree->right->cmd, O_RDONLY);
	if (file == -1)
	{
		ft_printf("42sh: no such file or directory: %s\n", tree->right->cmd);
		return ;
	}
	father = fork();
	if (father > 0)
		wait(&father);
	else
	{
		dup2(file, 0);
		if (execve(cmd[0], cmd, env) < 0)
			ft_printf(": Execve Failed.\n");
		close(file);
		exit(0);
	}
}

static void			execve_chev(int fd[2], char **cmd, char **env)
{
	dup2(fd[0], 0);
	if (execve(cmd[0], cmd, env) < 0)
		ft_printf(": Execve Failed.\n");
	close(fd[0]);
	exit(0);
}

void				fn_double_chev(t_tree *tree, char **env, t_env *count)
{
	char	*line;
	int		father;
	char	**cmd;
	int		fd[2];
	int		i;

	i = 0;
	line = ft_strnew(0);
	pipe(fd);
	while (ft_strcmp(line, tree->right->cmd))
	{
		ft_printf("heredoc> ");
		if (i)
			ft_putendl_fd(line, fd[1]);
		line = ft_termcaps(9);
		i++;
	}
	close(fd[1]);
	cmd = fn_commande(tree->left->cmd, env, count);
	father = fork();
	if (father > 0)
		wait(&father);
	else
		execve_chev(fd, cmd, env);
	ft_strdel(&line);
}

t_tree				*verif_chev(t_tree *tree)
{
	t_tree	*tmp;

	tmp = tree;
	while (tmp->father && tmp->father->cmd[0] != '|'
			&& tmp->father->cmd[0] != '>')
		tmp = tmp->father;
	if (tmp->father && (tmp->father->cmd[0] == '|'
			|| tmp->father->cmd[0] == '>'))
		return (tmp);
	else
		return (tree);
}
