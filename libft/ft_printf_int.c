/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:15:27 by alvicina          #+#    #+#             */
/*   Updated: 2023/11/24 10:43:56 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_int(int c)
{
	int	len;
	int	len2;

	len = 0;
	len2 = 0;
	if (c == -2147483648)
		return (ft_printf_str("-2147483648"));
	if (c < 0)
	{
		c = c * (-1);
		if (ft_printf_char ('-') == -1)
			return (-1);
		len2 = len2 + 1;
	}
	if (c > 9)
	{
		len = ft_printf_int(c / 10);
		if (len == -1)
			return (len);
		len2 = len2 + len;
	}
	if (ft_printf_char(c % 10 + '0') == -1)
		return (-1);
	return (len2 = len2 + 1);
}
