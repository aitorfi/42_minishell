/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:41:52 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 14:45:32 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*compare the null-ter-minated strings s1 and s2.The strncmp() function 
compares not more than n characters.  Because strncmp() is designed 
for comparing strings rather than binary data, characters that 
appear after a `\0' character are not compared.The strcmp() 
and strncmp() functions return an integer greater than, equal
to, or less than 0, according as the string s1 is greater than, equal to, or
less than the string s2.  The comparison is done using unsigned characters,
so that `\200' is greater than `\0'*/

#include "libft.h"
/*
int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	main(void)
{
	char	s11[] = "VicInay";
	char	s21[] = "VicInay";
	char	c11[] = "Vicinay";
	char	c21[] = "VicInay";
	char	r11[] = "Vicinay";
	char	r21[] = "Vicinay";
	size_t	n;

	n = 15;
	printf("%d ft test1\n", ft_strncmp(s11, s21, n));
	printf("%d or test1\n", strncmp(s11, s21, n));
	printf("%d ft test2\n", ft_strncmp(c11, c21, n));
	printf("%d or test2\n", strncmp(c11, c21, n));
	printf("%d ft test3\n", ft_strncmp(r11, r21, n));
	printf("%d or test3\n", strncmp(r11, r21, n));
	return (0);
}
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (s1[i] == 0 || s2[i] == 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
