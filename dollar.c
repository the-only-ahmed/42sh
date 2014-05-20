/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 09:49:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 10:22:27 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*var_dollar(char **var)
{
	char	*str;
	int		a;

	str = NULL;
	a = 1;
	if (ft_strchr(*var, '/') && ft_strchr(*var, '.'))
	{
		if (ft_strchr(*var, '/') - ft_strchr(*var, '.') > 0)
			a = 0;
	}
	if (ft_strchr(*var, '/') && a)
	{
		str = ft_strsub(*var, ft_strchr(*var, '/') - *var, ft_strlen(*var));
		*var = ft_strsub(*var, 0, ft_strchr(*var, '/') - *var);
	}
	else if (ft_strchr(*var, '.'))
	{
		str = ft_strsub(*var, ft_strchr(*var, '.') - *var, ft_strlen(*var));
		*var = ft_strsub(*var, 0, ft_strchr(*var, '.') - *var);
	}
	return (str);
}

static char		*var_line(char *line, char *var, int i)
{
	int		len;

	len = ft_strlen(var);
	while (len)
	{
		line = decale_word(line, i);
		len--;
	}
	return (line);
}

char			*dollar(char *line, int *i, char **env)
{
	int		len;
	char	*var;
	char	*str;

	str = NULL;
	find_word3(&line[*i], &var, '$', '$');
	line = var_line(line, var, *i);
	str = var_dollar(&var);
	len = search_exp(&var[1], env);
	if (len >= 0)
	{
		line = ft_strinjoin(line, &env[len][ft_strlen(var)], *i);
		*i += ft_strlen(&env[len][ft_strlen(var)]) - 1;
		if (str)
		{
			line = ft_strinjoin(line, str, *i + 1);
			*i += ft_strlen(str);
			ft_strdel(&str);
		}
	}
	else
		(*i)--;
	return (line);
}
