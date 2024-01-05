/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:52:37 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 17:40:44 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The bzero() function writes n zeroed bytes to the string s.  If n is zero,
bzero() does nothing.*/

#include "libft.h"
/*
void	ft_bzero(void *s, size_t n);

int	main(void)
{
	char	s[] = "Hola Alejandro Vicinay";
	char	l[] = "Hola Alejandro Vicinay";

	size_t	n;
	int		i;

	n = 7;
	ft_bzero(s, n);
	i = 0;
	while (i < 20)
	{	
		printf("%d ", s[i]);
		i++;
	}
	bzero(l, n);
	printf("\n");
	i = 0;
	while (i < 20)
	{	
		printf("%d ", l[i]);
		i++;
	}
	return (0);
}
*/
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)(s + i)) = 0;
		i++;
	}
}
