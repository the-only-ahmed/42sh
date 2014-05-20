/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 07:53:12 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 12:04:34 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_execve(char **line, char **env, int *bin, char *cmd)
{
	int		id;
	int		i;

	i = 0;
	id = fork();
	if (id == 0)
	{
		if (execve(line[0], line, env) < 0)
		{
			ft_putstr(cmd);
			ft_putstr(": command not found\n");
			*bin = -1;
			exit(1);
		}
		if (line)
			free_tab(&line);
		exit(0);
	}
	if (id > 0)
		waitpid(id, &i, 0);
	g_glob.var = i;
	if (i != 0)
		*bin = -1;
}
