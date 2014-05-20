/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 06:01:30 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 16:51:55 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*delete_bs(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && !back_line(str, i))
		{
			j = i;
			while (str[j] != '\0')
			{
				str[j] = str[j + 1];
				j++;
			}
		}
		i++;
	}
	return (str);
}

char	**ft_trait(char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		cmd[i] = delete_bs(cmd[i], '\\');
		i++;
	}
	return (cmd);
}

int		back_line(char *str, int i)
{
	int		b;

	b = 0;
	i--;
	while (i > 0 && str[i] == '\\')
	{
		if (str[i] == '\\')
			b++;
		i--;
	}
	if (b % 2 == 0)
		return (1);
	return (0);
}
