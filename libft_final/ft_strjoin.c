/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:52:28 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 17:17:22 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*he reservado memoria para la nueva string. He añadido + 1 al malloc
por si me pasan NULL en ambos strings. Para poder merter el NULL.
A partir de la posicin 0 del string nuevo, copio el s1. A partir de 
donde se ha quedado el NULL en s1 copio s2.*/

#include "libft.h"
/*/
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2);

int	main(void)
{
	char	s1[] = "";
	char	s2[] = "";

	printf("strjoin:%x\n", *ft_strjoin(s1, s2));
	return (0);
}

*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	a;
	size_t	j;
	char	*p;

	a = ft_strlen(s1);
	j = ft_strlen(s2);
	p = malloc(a + j + 1);
	if (p == 0)
		return (0);
	ft_strlcpy(p, (char *)s1, j + a + 1);
	ft_strlcpy(&p[a], (char *)s2, j + a + 1);
	return (p);
}
