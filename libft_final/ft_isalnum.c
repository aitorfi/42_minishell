/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:27 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/20 19:14:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	ft_isalnum(int c);

int	main(void)
{
	unsigned char	c;
	int				x;

	c = 40;
	x = ft_isalnum(c);
	printf("%d ft\n", x);
	x = isalnum(c);
	printf("%d or\n", x);
	return (0);
}
*/
int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}
