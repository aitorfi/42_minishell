/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:19:32 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:38:20 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*A cada carácter de la string ’s’, aplica la
función ’f’ dando como parámetros el índice de cada carácter dentro de 
’s’ y el propio carácter. Genera una nueva string con el resultado 
del uso sucesivo de ’f’*/

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>

char    ft_it(unsigned int i, char c);
char    *ft_strmapi(char const *s, char (*f)(unsigned int i, char c));

int main(void)
{
    char const  s[]= "LoReM iPsUm";
    char        *resultado = ft_strmapi(s, ft_it);
    
    printf("ft_strmapi: %s\n", resultado);
    return (0);
}

char    ft_it(unsigned int i, char c)
{
    i = 0;
    if (c >= 97 && c <= 122)
        c = c - 32;
    return (c); 
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_s;

	new_s = ft_calloc(1, ft_strlen(s) + 1);
	if (new_s == 0)
		return (0);
	i = -1;
	while (s[++i] != 0)
		new_s[i] = f(i, s[i]);
	return (new_s);
}
