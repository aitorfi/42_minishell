/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:50:59 by alvicina          #+#    #+#             */
/*   Updated: 2023/11/24 11:27:03 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
size_t	ft_strlen(const char *s);

int	main(void)
{
	const char	s[] = "pepe";
	int			x;

	x = ft_strlen(s);
	printf("%d ft\n", x);
	x = strlen(s);
	printf("%d or\n", x);
	return (0);
}
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}
