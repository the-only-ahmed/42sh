/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 07:12:25 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 21:32:26 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		xxx(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

static char		*the_director(DIR *directory, char *pattern, char *path, int *i)
{
	struct dirent	*lecture;
	char			*str;
	char			*ch;

	str = ft_strnew(0);
	while ((lecture = readdir(directory)) != NULL)
	{
		ch = ft_strnew(0);
		if ((!pattern || match(lecture->d_name, pattern)) &&
			lecture->d_name[0] != '.')
		{
			if (ft_strcmp(path, "./"))
				ch = ft_strjoin(path, lecture->d_name);
			else
				ch = ft_strdup(lecture->d_name);
			if (*i)
				str = ft_strjoin(str, " ");
			str = ft_strjoin(str, ch);
			(*i)++;
		}
		ft_strdel(&ch);
	}
	return (str);
}

static char		*the_director2(DIR *directory, char *patern, char *path, int *i)
{
	struct dirent	*lecture;
	char			*str;
	char			*ch;

	str = ft_strnew(0);
	while ((lecture = readdir(directory)) != NULL)
	{
		ch = ft_strnew(0);
		if ((!patern || xxx(lecture->d_name, patern)) &&
			lecture->d_name[0] != '.')
		{
			if (ft_strcmp(path, "./"))
				ch = ft_strjoin(path, lecture->d_name);
			else
				ch = ft_strdup(lecture->d_name);
			if (*i)
				str = ft_strjoin(str, " ");
			str = ft_strjoin(str, ch);
			(*i)++;
		}
		ft_strdel(&ch);
	}
	return (str);
}

char			*find_match(DIR *directory, char *pattern, char *path, int x)
{
	char			*str;
	int				i;

	i = 0;
	if (x)
		str = the_director(directory, pattern, path, &i);
	else
		str = the_director2(directory, pattern, path, &i);
	if (!i)
	{
		if (ft_strcmp(path, "./") && pattern)
			return (ft_strjoin(path, pattern));
		return (pattern);
	}
	return (str);
}
