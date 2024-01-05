/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:30:47 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 14:21:01 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The memcmp() function compares byte string s1 against byte string s2. Both
strings are assumed to be n bytes long. The memcmp() function returns
 zero if the two strings are identical, other-
wise returns the difference between the first two differing bytes (treated as
unsigned char values, so that `\200' is greater than `\0', for example).
Zero-length strings are always identical. */

#include "libft.h"
/*
int	ft_memcmp(const void *s1, const void *s2, size_t n);

int	main(void)
{
	char	s11[] = "VicInay";
	char	s21[] = "Vicinay";
	char	c11[] = "Vicinay";
	char	c21[] = "VicInay";
	char	r11[] = "Vicinay";
	char	r21[] = "Vicinay";
	size_t	n;

	n = 4;
	printf("%d ft test1\n", ft_memcmp(s11, s21, n));
	printf("%d or test1\n", memcmp(s11, s21, n));
	printf("%d ft test2\n", ft_memcmp(c11, c21, n));
	printf("%d or test2\n", memcmp(c11, c21, n));
	printf("%d ft test3\n", ft_memcmp(r11, r21, n));
	printf("%d or test3\n", memcmp(r11, r21, n));
	return (0);
}
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*p1;
	char	*p2;

	p1 = (char *)s1;
	p2 = (char *)s2;
	i = 0;
	while (p1[i] == p2[i] && i < n)
	{
		if (i == n - 1)
			return (0);
		i++;
	}
	if (p1[i] != p2[i] && i < n)
		return ((unsigned char)p1[i] - (unsigned char)p2[i]);
	else
		return (0);
}
