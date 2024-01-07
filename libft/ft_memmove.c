/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:55:02 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:22:15 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The memmove() function copies len bytes from string src to string dst.
The two strings may overlap; the copy is always done in a non-destructive
manner. The memmove() function returns the original value of dst.
El solapamiento da problemas cuando d > s (las direcciones de memoria
pueden llegar a coincidir si len > d - s). Para gstionar esto nos vamos 
len - 1 posiciones hacia delante tanto en d como en s y copiamos hacia atras*/

#include "libft.h"
/*
void	*ft_memmove(void *dst, const void *src, size_t len);

int	main(void)
{
	char	src[] = "Hola Alejandro Vicinay";
	char	src2[] = "Hola Alejandro Vicinay";
	size_t	len;

	len = 5;
	ft_memmove(src + 5, src + 3, len);
	printf("%s ", src);
	printf("\n");
	memmove(src2 + 5, src2 + 3, len);
	printf("%s ", src2);
	return (0);
}
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (d < s)
	{
		i = -1;
		while (++i < len)
		{
			*(d + i) = *(s + i);
		}
	}
	if (d > s)
	{
		d = d + len - 1;
		s = s + len - 1;
		i = -1;
		while (++i < len)
		{
			*(d - i) = *(s - i);
		}
	}
	return (dst);
}
