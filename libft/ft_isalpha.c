/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:25:57 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/20 19:14:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	ft_isalpha(int c);

int	main(void)
{
	unsigned char	c;
	int				x;
	int				s;

	c = 126;
	x = ft_isalpha(c);
	s = isalpha(c);
	printf("%d hola ", x);
	printf("%d hola2 ", s);
	return (0);
}
*/
int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	else
		return (0);
}
