/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:25:17 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 13:18:59 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strdup() function allocates sufficient memory for a copy of the
string s1, does the copy, and returns a pointer to it.  The pointer may
subsequently be used as an argument to the function free(3).
If insufficient memory is available, NULL is returned*/

#include "libft.h"
/*
#include <string.h>

char	*ft_strdup(const char *s1);

int	main(void)
{
	char	s1[] = "lorem ipsum dolor sit amet";
	
	printf("mi funcion: %s\n", ft_strdup(s1));
	printf("original: %s\n", strdup(s1));
	free(ft_strdup(s1));
	free(strdup(s1));
	return (0);
}
*/
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		j;

	i = 0;
	while (s1[i] != 0)
		i++;
	s2 = malloc(i + 1);
	if (s2 == 0)
		return (0);
	j = 0;
	while (j <= i)
	{
		s2[j] = s1[j];
		j++;
	}
	return (s2);
}
