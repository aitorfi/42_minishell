/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:05:23 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:23:18 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_str(char *c)
{
	int	i;
	int	len2;

	if (c == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		else
			return (6);
	}
	i = -1;
	len2 = 0;
	while (c[++i])
	{
		if (write(1, &c[i], 1) == -1)
			return (-1);
		len2 = len2 + 1;
	}
	return (len2);
}
