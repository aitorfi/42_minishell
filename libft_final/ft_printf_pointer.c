/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:53:31 by alvicina          #+#    #+#             */
/*   Updated: 2023/11/24 10:43:59 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_pointer(unsigned long long number)
{
	int	len2;

	len2 = 0;
	if (ft_printf_str("0x") == -1)
		return (-1);
	len2 = len2 + 2;
	len2 = len2 + ft_printf_hexa(number, 'x');
	return (len2);
}
