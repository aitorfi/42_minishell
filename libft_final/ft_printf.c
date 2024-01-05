/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:29:12 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:22:32 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(va_list args, char c, int *len2)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_printf_char(va_arg(args, int));
	else if (c == 's')
		len = ft_printf_str(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		len = ft_printf_int(va_arg(args, int));
	else if (c == 'u')
		len = ft_printf_unsg_int(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		len = ft_printf_hexa(va_arg(args, unsigned int), c);
	else if (c == 'p')
		len = ft_printf_pointer((unsigned long)va_arg(args, void *));
	else if (c == '%')
		len = ft_printf_char('%');
	if (len == -1)
		return (-1);
	return (*len2 = *len2 + len);
}

int	ft_printf(char const *pointer, ...)
{
	int		i;
	int		len2;
	va_list	args;

	va_start(args, pointer);
	i = -1;
	len2 = 0;
	while (pointer[++i])
	{
		if (pointer[i] == '%' && pointer[i + 1] != 0)
		{
			if (ft_format(args, pointer[i + 1], &len2) == -1)
				return (-1);
			i++;
		}
		else
		{
			if (ft_printf_char(pointer[i]) == -1)
				return (-1);
			len2 = len2 + 1;
		}
	}
	return (va_end(args), len2);
}
/*
int	main(void)
{
	char			x = 'h';
	char			c = 'u';
	char			d = 'q';
	char			*p = 0;
	int				entero = 3;
	unsigned int	sinsigno = 5;
	int				hex = 16;
	
	ft_printf(" %c\n hola\n %c\n %c\n %s\n %d\n %u\n %x\n %X\n %p\n", 
	x, c, d, p, entero, sinsigno, hex, hex, &p);
	ft_printf("%%");
	return (0);
}
*/
