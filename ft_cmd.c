/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 15:54:42 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/21 17:50:39 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**fn_commande(char *str, char **env, t_env *count)
{
	char	**cmd;
	char	*path;

	cmd = ft_strsplit_spaces(str, ' ', 0);
	if (ft_strchr(cmd[0], '/'))
	{
		path = ft_strsub(cmd[0], 0, (ft_strrchr(cmd[0], '/') - cmd[0]) + 1);
		cmd[0] = ft_strrchr(cmd[0], '/') + 1;
	}
	else
		path = create_path(cmd[0], env, count);
	if (path == NULL)
		path = "/";
	if (path)
		cmd[0] = ft_strjoin(path, cmd[0]);
	return (cmd);
}
