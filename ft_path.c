/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 19:23:57 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 14:27:49 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*path_search(char *command, char **directories)
{
	DIR				*directory;
	struct dirent	*lecture;
	char			*str;
	int				i;

	i = 0;
	while (directories[i] != NULL)
	{
		if ((directory = opendir(directories[i])) != NULL)
		{
			while ((lecture = readdir(directory)) != NULL)
			{
				if (ft_strcmp(lecture->d_name, command) == 0)
				{
					str = ft_strdup(directories[i]);
					free_tab(&directories);
					return (str);
				}
			}
		}
		i++;
	}
	free_tab(&directories);
	return (NULL);
}

char			*create_path(char *command, char **env, t_env *count)
{
	char	**path;
	int		i;

	i = 0;
	if (count->path == -1)
		return (NULL);
	path = ft_strsplit(&env[count->path][5], ':');
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path_search(command, path));
}

char			*pathing(char *str, int *i)
{
	char	*path;

	*i = 0;
	*i = ft_strchr(str, '/') - str;
	path = ft_strsub(str, 0, *i + 1);
	return (path);
}

char			*pathing2(char *str, int *i)
{
	char	*path;

	*i = 0;
	*i = ft_strrchr(str, '/') - str;
	path = ft_strsub(str, 0, *i + 1);
	return (path);
}
