/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:36:00 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/20 19:14:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	ft_isdigit(int c);

int	main(void)
{
	unsigned char	c;
	int				x;
	int				s;

	c = 57;
	x = ft_isdigit(c);
	s = isdigit(c);
	printf("%d ft \n", x);
	printf("%d or", s);
	return (0);
}
*/
int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}
