/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:56:57 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:33:38 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*A cada carácter de la string ’s’, aplica la función ’f’ dando como 
parámetros el índice de cada carácter dentro de ’s’ y la dirección 
del propio carácter, que podrá modificarse si es necesario.*/

#include "libft.h"
/*
#include <stdio.h>

void	ft_it(unsigned int i, char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

int	main(void)
{
	char	s[] = "Hola Mundo";

	ft_striteri(s, ft_it);
	printf("ft_striteri: %s\n", s);
	return (0);
}

void	ft_it(unsigned int i, char *s)
{
	i = 0;
	if (*s >= 97 && *s <= 122)
		*s = *s - 32;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != 0)
	{
		f(i, &s[i]);
		i++;
	}
}
