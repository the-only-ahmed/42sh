/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bk_qotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 05:47:35 by jyim              #+#    #+#             */
/*   Updated: 2014/03/26 08:14:11 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		verif_bq(char *cmd)
{
	int		i;
	int		q;
	char	qt;

	i = 0;
	qt = 0;
	q = 0;
	while (cmd[i])
	{
		q = verif_token(cmd[i], q, &qt);
		if (q && qt == '`')
			return (1);
		i++;
	}
	return (0);
}

char	*father_bq(char *ret, char **env, t_env *count)
{
	int		fd;
	int		x;
	char	*line;
	char	**cmd;

	wait(NULL);
	fd = open(".read", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ret[0])
			ret = ft_strjoin(ret, " ");
		ret = ft_strjoin(ret, line);
		ft_strdel(&line);
	}
	cmd = fn_commande("rm .read", env, count);
	ft_execve(cmd, env, &x, "rm");
	close(fd);
	return (ret);
}

char	*bq_fd(t_tree *tree, char **env, t_env *count)
{
	pid_t	pid;
	int		fd;
	char	*ret;

	ret = ft_strnew(0);
	pid = fork();
	if (pid)
		ret = father_bq(ret, env, count);
	if (!pid)
	{
		fd = open(".read", O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			return (NULL);
		dup2(fd, 1);
		ft_argc(tree, env, count);
		close(fd);
		exit(0);
	}
	return (ret);
}

char	*bq(char *cmd, char **env, t_env *count)
{
	int		i;
	int		end;
	char	**tab;
	t_tree	*tree;

	i = 0;
	tab = ft_strsplit_spaces(cmd, ' ', 1);
	while (tab[i])
	{
		if (tab[i][0] == '`')
		{
			end = ft_strlen(tab[i]);
			tab[i][end - 1] = '\0';
			tab[i] = tab[i] + 1;
			tree = parser(tab[i]);
			tab[i] = bq_fd(tree, env, count);
			free_tree(&tree);
		}
		i++;
	}
	cmd = ft_all_strjoin(tab);
	return (cmd);
}
