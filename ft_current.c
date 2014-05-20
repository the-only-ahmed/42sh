/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 05:09:01 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 11:35:20 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"

char	*ft_dup_char(char c)
{
	char	*str;

	str = malloc(sizeof(*str) * 2);
	str[0] = c;
	str[1] = 0;
	return (str);
}

char	*ft_realloc_one(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len + 1));
	while (str[i] != 0)
	{
		tmp[i] = str[i];
		i++;
	}
	ft_strdel(&str);
	tmp[i] = 0;
	tmp[len + 1] = 0;
	return (tmp);
}
