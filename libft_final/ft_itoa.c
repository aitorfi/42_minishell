/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:10:47 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:21:59 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*1) hago el filtro de si es negativo o no. 2) Cuento cuantos elementos 
tendra el string con las decenas. 3) Lo ajusto por si es negativo, para el 
nulo y para el caso de que nos pasen un nulo. 4)Aloco la memoria para los 
elementos. 5) relleno los elementos. resto menos 1 al num char al ppio
para pasar elementos a indice. El indice lo pongo en -1 para que no 
me pise el nulo del string al final. A la primera posicion le meto 
un nulo, que en caso de no se nulo el numero a convertir se pisara
en el bucle. 6) dentro de bucle utilizo el resto del numero que voy 
diviendo entre 10 para pintar los digitos */

#include "libft.h"
/*
#include <stdlib.h>
#include <stdio.h>

char	*ft_itoa(int n);

int	main(void)
{
	int	n;

	n = 0;
	printf("ft_itoa: %s\n", ft_itoa(n));
	return (0);
}
*/
static char	*ft_fill_itoa(char *number, int n2, int num_chars, char neg)
{
	num_chars = num_chars - 1;
	number[0] = 48;
	if (neg == -1)
		number[0] = '-';
	while (n2 > 0)
	{
		number[num_chars - 1] = (n2 % 10) + 48;
		n2 = n2 / 10;
		num_chars--;
	}
	return (number);
}

static int	ft_count(int n)
{
	int		num_chars;
	int		num_itoa;

	num_chars = 0;
	while (n > 0)
	{
		num_itoa = n / 10;
		n = num_itoa;
		num_chars++;
	}
	return (num_chars);
}

char	*ft_itoa(int n)
{
	int		num_chars;
	char	neg;
	char	*number;
	int		n2;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 1;
	if (n < 0)
	{
		neg = -1;
		n = n * (-1);
	}
	n2 = n;
	num_chars = ft_count(n);
	if (neg == -1)
		num_chars = num_chars + 1;
	num_chars = num_chars + 1;
	if (n2 == 0)
		num_chars = 2;
	number = ft_calloc(1, num_chars);
	if (number == 0)
		return (0);
	number = ft_fill_itoa(number, n2, num_chars, neg);
	return (number);
}
