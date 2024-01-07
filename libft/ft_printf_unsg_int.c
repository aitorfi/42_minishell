/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsg_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:37:23 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:24:09 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_unsg_int(unsigned int c)
{
	int	len;
	int	len2;

	len = 0;
	len2 = 0;
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
