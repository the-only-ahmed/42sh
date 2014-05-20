/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 22:33:24 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/11 07:53:28 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_clear_pwd(char *pwd)
{
	int		i;

	i = 0;
	if (pwd[ft_strlen(pwd) - 1] == '/')
		pwd[ft_strlen(pwd) - 1] = '\0';
	while (pwd[i] != '\0')
	{
		if (pwd[i] == '.' && pwd[i + 1] == '.')
			pwd = fn_pwd_2(pwd, &i, 3);
		pwd = fn_pwd_1(pwd, &i);
		i++;
	}
	pwd = delete_chars(pwd, '/');
	pwd[0] = '/';
	return (pwd);
}

char	*fn_pwd_1(char *pwd, int *i)
{
	int		j;
	int		x;

	if (pwd[*i] == '.' && pwd[*i + 1] == '/' && pwd[*i - 1] == '/')
	{
		x = 0;
		while (x < 2)
		{
			j = *i;
			while (pwd[j] != '\0')
			{
				pwd[j] = pwd[j + 1];
				j++;
			}
			x++;
			(*i)--;
		}
	}
	return (pwd);
}

char	*fn_pwd_2(char *pwd, int *i, int x)
{
	int		j;
	int		slash;

	slash = 0;
	while (slash < 2 || (pwd[*i] == '/' && *i == 0))
	{
		if (pwd[*i] != '/')
			x++;
		else
			slash++;
		(*i)--;
	}
	(*i)++;
	while (x > 0)
	{
		j = *i;
		while (pwd[j] != '\0')
		{
			pwd[j] = pwd[j + 1];
			j++;
		}
		x--;
	}
	return (pwd);
}
