/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 19:23:48 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/26 10:56:31 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				ft_setenv(char **line2, char **env, int *bin)
{
	int		i;

	i = 0;
	if (line2[1] == NULL)
	{
		*bin = -1;
		return (0);
	}
	if (line2[2] == NULL)
		line2[2] = ft_strnew(0);
	while (env[i] != NULL)
	{
		if (ft_strncmp(line2[1], env[i], ft_strlen(line2[1])) == 0)
		{
			line2[1] = ft_strjoin(line2[1], "=");
			env[i] = ft_strjoin(line2[1], line2[2]);
			return (0);
		}
		i++;
	}
	line2[1] = ft_strjoin(line2[1], "=");
	env[i] = ft_strjoin(line2[1], line2[2]);
	return (0);
}

static char		**ft_unsetenv2(char **env, t_env **count, char **line2, int j)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(line2[j], env[i], ft_strlen(line2[j])) == 0)
		{
			while (env[i + 1])
			{
				env[i] = ft_strdup(env[i + 1]);
				i++;
			}
			ft_strdel(&env[i]);
			*count = reset_count(env, *count);
			(*count)->boll = 0;
			return (env);
		}
		i++;
	}
	return (env);
}

int				ft_unsetenv(char **line2, char **env, t_env *count, int *bin)
{
	int		j;

	j = 1;
	count->boll = 1;
	if (line2[1] == NULL || ft_strchr(line2[1], '=') != NULL)
	{
		*bin = -1;
		return (-1);
	}
	while (line2[j])
	{
		if (!ft_strcmp(line2[j], "_"))
		{
			ft_putendl("42sh : read-only variable: _");
			j++;
			continue ;
		}
		env = ft_unsetenv2(env, &count, line2, j);
		if (!count->boll)
			return (0);
		j++;
	}
	return (0);
}

t_env			*reset_count(char **env, t_env *count)
{
	int		i;

	i = 0;
	count->path = -1;
	count->pwd = -1;
	count->home = -1;
	count->old = -1;
	if (!env)
		return (count);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			count->path = i;
		else if (ft_strncmp("PWD", env[i], 3) == 0)
			count->pwd = i;
		else if (ft_strncmp("HOME", env[i], 4) == 0)
			count->home = i;
		else if (ft_strncmp("OLDPWD", env[i], 6) == 0)
			count->old = i;
		i++;
	}
	return (count);
}

char			**make_env(t_env **count, char **environ)
{
	int		i;
	int		length;
	char	*ret;
	char	**env;

	i = 0;
	length = 0;
	while (environ[length++])
		i++;
	i = 0;
	env = (char**)malloc(sizeof(char*) * (length));
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	*count = reset_count(env, *count);
	if ((*count)->pwd == -1)
	{
		ret = ft_strdup("PWD=");
		env = ft_set_modif(env, ft_strjoin(ret, getcwd(NULL, 0)));
	}
	return (env);
}
