/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:37:07 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 14:39:35 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The memchr() function locates the first occurrence of c (converted to an
unsigned char) in string s.The memchr() function returns a pointer 
to the byte located, or NULL if no
such byte exists within n bytes.*/

#include "libft.h"
/*
void	*ft_memchr(const void *s, int c, size_t n);

int	main(void)
{
	char	s[] = "Hola Mundo";
	int		c;
	size_t	n;

	c = 'o';
	n = 10;
	printf("%p ft test1\n", ft_memchr(s, c, n));
	printf("%p or test1\n", memchr(s, c, n));
	c = 'p';
	n = 10;
	printf("%p ft test2\n", ft_memchr(s, c, n));
	printf("%p or test2\n", memchr(s, c, n));
	c = 'n';
	n = 10;
	printf("%p ft test3\n", ft_memchr(s, c, n));
	printf("%p or test3\n", memchr(s, c, n));
	c = 0;
	n = 10;
	printf("%p ft test4\n", ft_memchr(s, c, n));
	printf("%p or test4\n", memchr(s, c, n));
	c = 0;
	n = 11;
	printf("%p ft test5\n", ft_memchr(s, c, n));
	printf("%p or test5\n", memchr(s, c, n));
	c = 5;
	n = 15;
	printf("%p ft test6\n", ft_memchr(s, c, n));
	printf("%p or test6\n", memchr(s, c, n));
	c = 5;
	n = 4;
	printf("%p ft test7\n", ft_memchr(s, c, n));
	printf("%p or test7\n", memchr(s, c, n));
	return (0);
}

*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	x;
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	x = (unsigned char)c;
	if (n == 0)
		return (0);
	i = 0;
	while (p[i] != x && i < n)
	{
		if (i == n - 1)
			return (0);
		i++;
	}
	return ((void *)(p + i));
}
