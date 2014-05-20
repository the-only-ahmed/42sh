/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spec2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 10:53:02 by jyim              #+#    #+#             */
/*   Updated: 2014/03/19 10:53:20 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*fn_put3(char *str, int *i)
{
	if (str[*i] == '&')
	{
		if (str[*i + 1] == '&')
		{
			(*i)++;
			return ("&&");
		}
		return ("&");
	}
	return (NULL);
}

char		*fn_put2(char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			(*i)++;
			return ("<<");
		}
		return ("<");
	}
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			(*i)++;
			return (">>");
		}
		else if (str[*i + 1] == '|')
		{
			(*i)++;
			return (">|");
		}
		return (">");
	}
	return (fn_put3(str, i));
}

char		*fn_put(char *str, int *i)
{
	if (str[*i] == ';')
	{
		if (str[*i + 1] == ';')
		{
			(*i)++;
			return (";;");
		}
		return (";");
	}
	if (str[*i] == '|')
	{
		if (str[*i + 1] == '|')
		{
			(*i)++;
			return ("||");
		}
		return ("|");
	}
	return (fn_put2(str, i));
}
