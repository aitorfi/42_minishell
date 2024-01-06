/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:59:47 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 12:39:40 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*1) Genero el string de punteros. Tantos punteros como palabras + puntero 
a NULL. Para saber cuantas palabras las cuento con un bucle en donde recorro
el string e identifico los elementos delimitadores que me generan palabras. 
los guado en COUNT y le sumo + 1 para el NULL. Con el numero de palabras
creo otro bucle para ir generando los substrings y liberarlos en caso de 
error */

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);

int	main(void)
{
	char	p[] = "hello!";
	char	c;

	c = ' ';
	printf("ft_split: %p\n", ft_split(p, c));
	return (0);
}
*/
static size_t	ft_count_word(char const *s, char c)
{
	size_t	init;
	size_t	count;
	size_t	final;

	final = 0;
	count = 0;
	init = 0;
	while (s[init] != 0)
	{
		init = final;
		while (s[init] == c && s[init] != 0)
			init++;
		if (s[init] != c && s[init] != 0)
			count++;
		final = init;
		while (s[final] != c && s[final] != 0)
			final++;
		init = final;
	}
	return (count);
}

static char	**ft_free(char **split, size_t limit)
{
	limit = 0;
	while (split[limit] != 0)
	{
		free(split[limit]);
		limit++;
	}
	free(split);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	limit;
	size_t	init;
	size_t	final;

	split = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (0);
	limit = -1;
	final = 0;
	while (++limit < ft_count_word(s, c))
	{
		init = final;
		while (s[init] == c && s[init] != 0)
			init++;
		final = init;
		while (s[final] != c && s[final] != 0)
			final++;
		split[limit] = malloc (sizeof(char) * (final - init + 1));
		if (split[limit] == 0)
			return (ft_free(split, limit));
		ft_strlcpy(split[limit], (char *)(s + init), final - init + 1);
	}
	split[limit] = 0;
	return (split);
}
