/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:54:38 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:25:12 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Genero una substr a partir de una substr. Primero fitro poor si el indice
start no es logico, po si el size es mayor del que necesito. Despues se copia*/

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	main(void)
{
	char			s1[] = "";
	unsigned int	start;
	size_t			len;

	start = 0;
	len = 0;
	printf("substring %s\n", ft_substr(s1, start, len));
	return (0);
}
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*p;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (p == 0)
		return (0);
	i = 0;
	while (i < len && s[start] != 0)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = 0;
	return ((char *)(p));
}
