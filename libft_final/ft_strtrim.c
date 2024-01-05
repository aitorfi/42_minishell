/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:14:27 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 13:03:18 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*He generado dos funciones adicionales para localizar desde donde y hasta
donde es la string resultante. He utilizado substring, en size le paso + 1 
porque le tengo que pasar elementos, oara el NULL*/

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set);

int	main(void)
{
	char	s1[] = "";
	char	set[] = "";

	printf("ft_strtrim: %s\n", ft_strtrim(s1, set));
	return (0);
}

*/
static size_t	ft_strtrim_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	c;
	size_t	init;

	c = 0;
	while (s1[c] != 0)
	{
		i = 0;
		while (s1[c] != set[i] && set[i] != 0)
			i++;
		if (s1[c] != set[i])
			break ;
		c++;
	}
	init = c;
	return (init);
}

static size_t	ft_strtrim_finish(char const *s1, char const *set)
{
	size_t	i;
	size_t	c;
	size_t	final;

	c = ft_strlen(s1);
	while (c >= 0)
	{
		i = 0;
		while (s1[c] != set[i] && set[i] != 0)
			i++;
		if (s1[c] != set[i])
			break ;
		c--;
	}
	final = c;
	return (final);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (*s1 == 0)
		return (ft_substr(s1, 0, 1));
	return (ft_substr(s1, ft_strtrim_start(s1, set),
			ft_strtrim_finish(s1, set) - ft_strtrim_start(s1, set) + 1));
}
