/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:11:27 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:24:55 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The strnstr() function locates the first occurrence of the null-terminated
string needle in the string haystack, where not more than len characters are
searched.  Characters that appear after a `\0' character are not searched.
Since the strnstr() function is a FreeBSD specific API, it should only be
used when portability is not a concern. If needle is an empty string,
 haystack is returned; if needle occurs nowhere
in haystack, NULL is returned; otherwise a pointer to 
the first character of the first occurrence of needle is returned.*/

#include "libft.h"
/*
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int	main(void)
{
	const char	haystack[] = "abc";
	const char	needle1[] = "abcdef";
	const char	needle2[] = "jan ";
	const char	needle3[] = "in";
	const char	needle4[] = "de ";
	const char	needle5[] = "ade";
	const char	needle6[2] = "";
	size_t		len;

	len = 20;
	printf("%p ft test1\n", ft_strnstr(haystack, needle1, len));
	printf("%p or test1\n", strnstr(haystack, needle1, len));
	
	printf("%p ft test2\n", ft_strnstr(haystack, needle2, len));
	printf("%p or test2\n", strnstr(haystack, needle2, len));
	printf("%p ft test3\n", ft_strnstr(haystack, needle3, len));
	printf("%p or test3\n", strnstr(haystack, needle3, len));
	printf("%p ft test4\n", ft_strnstr(haystack, needle4, len));
	printf("%p or test4\n", strnstr(haystack, needle4, len));
	printf("%p ft test5\n", ft_strnstr(haystack, needle5, len));
	printf("%p or test5\n", strnstr(haystack, needle5, len));
	printf("%p ft test6\n", ft_strnstr(haystack, needle6, len));
	printf("%p or test6\n", strnstr(haystack, needle6, len));
	return (0);
}
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	flag;

	flag = 0;
	if (needle[flag] == 0)
		return ((char *)(haystack));
	j = -1;
	while (++j < len && haystack[j] != 0)
	{
		i = 0;
		while (needle[i] != 0 && haystack[j + i] != 0
			&& needle[i] == haystack[j + i] && (j + i) < len)
			i++;
		if (needle[i] == 0)
			return ((char *)(haystack + j));
	}
	return ((char *)(0));
}
