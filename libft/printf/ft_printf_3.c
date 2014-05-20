/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 07:19:24 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 12:55:06 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		condition_2(const char *str, int *i, va_list ap)
{
	int		length;

	length = 0;
	if (sym_char(str, i))
	{
		if (str[*i + 1] != 'c')
		{
			length--;
			(*i)++;
		}
		length--;
		ft_putchar(va_arg(ap, int));
	}
	else if (str[*i + 1] == 's')
		length += ft_putstr(va_arg(ap, char*)) - 2;
	else if (str[*i + 1] == 'u')
		length += ft_putunsigned_int(va_arg(ap, unsigned int), 10) - 2;
	else if (str[*i + 1] == 'o')
		length += ft_putunsigned_int(va_arg(ap, unsigned int), 8) - 2;
	else if (str[*i + 1] == 'x')
		length += ft_putunsigned_int(va_arg(ap, unsigned int), 16) - 2;
	else
		length += condition_3(str, i, ap);
	return (length);
}

int		condition_3(const char *str, int *i, va_list ap)
{
	int		length;

	length = 0;
	if (str[*i + 1] == 'X')
		length += ft_putunsigned_int(va_arg(ap, unsigned int), 61) - 2;
	else if (str[*i + 1] == 'p')
	{
		ft_putstr("0x");
		length += ft_printpointeur(va_arg(ap, void*));
	}
	else if (str[*i + 1] == 'l' && str[*i + 2] == 'l' && str[*i + 3] == 'u')
	{
		length += ft_putunsigned_2long(va_arg(ap, unsigned long long)) - 4;
		*i += 2;
	}
	else
		length += condition_4(str, i, ap);
	return (length);
}

int		condition_4(const char *str, int *i, va_list ap)
{
	int		length;

	length = 0;
	if (str[*i + 1] == '%')
	{
		length--;
		ft_putchar('%');
	}
	else if (str[*i + 1] == '*' || (str[*i + 1] == '.' && str[*i + 2] == '*'))
		length += ft_all(str, i, ap);
	else if (str[*i + 1] < 97 || str[*i + 1] > 122)
	{
		(*i)--;
		length--;
	}
	return (length);
}
