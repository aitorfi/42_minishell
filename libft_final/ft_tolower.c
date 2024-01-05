/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:50:56 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/20 19:14:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	ft_tolower(int c);

int	main(void)
{
	char	c;

	c = 'A';
	printf("%c ft test1 ", ft_tolower(c));
	printf("%c or test1", tolower(c));
	printf("\n");
	c = 'a';
	printf("%c ft test2 ", ft_tolower(c));
	printf("%c or test2", tolower(c));
	printf("\n");
	c = '0';
	printf("%c ft test3 ", ft_tolower(c));
	printf("%c or test3", tolower(c));
	printf("\n");
	return (0);
}
*/
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c += 32;
		return (c);
	}
	else
		return (c);
}
