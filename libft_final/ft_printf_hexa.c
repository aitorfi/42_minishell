/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:50:56 by alvicina          #+#    #+#             */
/*   Updated: 2023/11/24 10:43:53 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hexa(unsigned long long number, char c)
{
	int	len;
	int	len2;

	len = 0;
	len2 = 0;
	if (number >= 16)
	{
		len = ft_printf_hexa(number / 16, c);
		if (len == -1)
			return (-1);
		len2 = len2 + len;
	}
	if (c == 'x')
		len2 = len2 + ft_printf_char("0123456789abcdef"[number % 16]);
	if (c == 'X')
		len2 = len2 + ft_printf_char("0123456789ABCDEF"[number % 16]);
	return (len2);
}
