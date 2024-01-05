/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:07:35 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 17:56:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strchr() function locates the first occurrence of c (converted to a
char) in the string pointed to by s.  The terminating null character is
considered to be part of the string; therefore if c is `\0', the functions
locate the terminating `\0'.    The strrchr() function is identical to 
strchr(), except it locates the
last occurrence of c.     The functions strchr() and strrchr() return a 
pointer to the located char-
acter, or NULL if the character does not appear in the string.*/

#include "libft.h"
/*
char	*ft_strchr(const char *s, int c);	

int	main(void)
{
	const char	s[] = "Hola1 Mundo";
	int		c;

	c = 'M';
	printf("%p ft test1\n", ft_strchr(s, c));
	printf("%p or test1\n", strchr(s, c));
	c = 'o';
	printf("%p ft test2\n", ft_strchr(s, c));
	printf("%p or test2\n", strchr(s, c));
	c = 'a';
	printf("%p ft test3\n", ft_strchr(s, c));
	printf("%p or test3\n", strchr(s, c));
	c = ' ';
	printf("%p ft test4\n", ft_strchr(s, c));
	printf("%p or test4\n", strchr(s, c));
	c = 'q';
	printf("%p ft test5\n", ft_strchr(s, c));
	printf("%p or test5\n", strchr(s, c));
	c = 0;
	printf("%p ft test6\n", ft_strchr(s, c));
	printf("%p or test6\n", strchr(s, c));
	return (0);
}
*/
char	*ft_strchr(const char *s, int c)
{
	char	x;
	int		i;

	x = (char)c;
	i = 0;
	while (s[i] != x && s[i] != 0)
		i++;
	if (s[i] == x)
		return ((char *)(s + i));
	else
		return ((char *)(0));
}
