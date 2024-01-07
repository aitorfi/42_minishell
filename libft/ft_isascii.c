/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:06:03 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/20 19:14:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	ft_isascii(int c);

int	main(void)
{
	int	c;
	int	s;

	c = 128;
	s = ft_isascii(c);
	printf("%d ft\n", s);
	s = isascii(c);
	printf("%d or\n", s);
	return (0);
}
*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
