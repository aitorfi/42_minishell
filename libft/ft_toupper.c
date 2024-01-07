/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:35:35 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/20 19:14:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	ft_toupper(int c);

int	main(void)
{
	char		c;
	r
	unsigned	x;

	c = '0';
	x = ft_toupper(c);
   	printf("%c ft\n", x);
	x = toupper(c);
	printf("%c or\n", x);
	return (0);	
}
*/
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c -= 32;
		return (c);
	}
	else
		return (c);
}
