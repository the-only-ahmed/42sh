/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 03:03:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 16:31:58 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*tilde(char *line, int *i, char **env, t_env *count)
{
	if (count->home < 0)
		(*i)--;
	else
	{
		if (line)
			line = decale_word(line, *i);
		else
			line = ft_strnew(0);
		line = ft_strinjoin(line, &env[count->home][5], *i);
		*i += ft_strlen(&env[count->home][5]) - 1;
	}
	return (line);
}

static char		*return_value(char *line, int i)
{
	char	*str;
	int		j;

	j = 0;
	while (j < 2)
	{
		line = decale_word(line, i);
		j++;
	}
	str = ft_itoa(g_glob.var);
	line = ft_strinjoin(line, str, i);
	ft_strdel(&str);
	return (line);
}

char			*variables(char *line, char **env, t_env *count)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] && line[i + 1] == '?'))
			line = return_value(line, i);
		else if (line[i] == '$' && back_line(line, i))
			line = dollar(line, &i, env);
		else if (line[i] == '~' && (!i || (i && line[i - 1] == ' ')))
			line = tilde(line, &i, env, count);
		i++;
	}
	return (line);
}

static char		*varies(char *ch, char **env)
{
	int		i;
	int		x;
	char	*line;

	i = -1;
	line = ft_strnew(0);
	while (env[++i])
	{
		if (ft_strncmp(env[i], ch, ft_strlen(ch)) == 0)
		{
			if (line[0])
				line = ft_strjoin(line, " ");
			line = ft_strjoin(line, ft_strsub(env[i], 0,
								ft_strchr(env[i], '=') - env[i]));
			x = i;
		}
	}
	if (ft_occ_nb(line, ' ') == 0)
	{
		ft_strdel(&line);
		line = ft_strdup(&env[x][(ft_strchr(env[x], '=') - env[x]) + 1]);
	}
	return (line);
}

char			*vars_tab(t_complete *s)
{
	int		i;

	i = 0;
	if (ft_strcmp(s->ch, "~") == 0)
		s->mot = tilde(s->mot, &i, s->env, s->count);
	else
		s->mot = varies(&(s->ch)[1], s->env);
	return (s->mot);
}
