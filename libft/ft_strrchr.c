/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:53:18 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 17:57:11 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strchr() function locates the first occurrence of c (converted to a
char) in the string pointed to by s.  The terminating null character is
considered to be part of the string; therefore if c is `\0', the functions
locate the terminating `\0'.    The strrchr() function is identical to 
strchr(), except it locates the
last occurrence of c.The functions strchr() and strrchr() return 
a pointer to the located char-
acter, or NULL if the character does not appear in the string.*/

#include "libft.h"
/*
char	*ft_strrchr(const char *s, int c);

int	main(void)
{
	const char	s[] = "Hola Mundo Alejandro";
	int			c;

	c = 'o';
	printf("%p ft test1\n", ft_strrchr(s, c));
	printf("%p or test1\n", strrchr(s, c));
	c = 'a';
	printf("%p ft test2\n", ft_strrchr(s, c));
	printf("%p or test2\n", strrchr(s, c));
	c = 'l';
	printf("%p ft test3\n", ft_strrchr(s, c));
	printf("%p or test3\n", strrchr(s, c));
	c = 'n';
	printf("%p ft test4\n", ft_strrchr(s, c));
	printf("%p or test4\n", strrchr(s, c));
	c = 0;
	printf("%d que hay\n", *ft_strrchr(s, c));
	printf("%p ft test5\n", ft_strrchr(s, c));
	printf("%p or test5\n", strrchr(s, c));
	c = 2;
	printf("%p ft test6\n", ft_strrchr(s, c));
	printf("%p or test6\n", strrchr(s, c));
	c = 'j';
	printf("%p ft test7\n", ft_strrchr(s, c));
	printf("%p or test7\n", strrchr(s, c));
	c = 'p';
	printf("%p ft test8\n", ft_strrchr(s, c));
	printf("%p or test8\n", strrchr(s, c));
	c = 'y';
	printf("%p ft test9\n", ft_strrchr(s, c));
	printf("%p or test9\n", strrchr(s, c));
	return (0);
}
*/
char	*ft_strrchr(const char *s, int c)
{
	char	x;
	int		i;

	x = (char)c;
	i = 0;
	while (s[i] != 0)
		i++;
	while (s[i] != x && i != 0)
		i--;
	if (s[i] == x)
		return ((char *)(s + i));
	else
		return ((char *)(0));
}
