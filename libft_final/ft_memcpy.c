/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:47:00 by alvicina          #+#    #+#             */
/*   Updated: 2023/12/19 13:04:48 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The memcpy() function copies n bytes from memory area src to memory area
dst.  If dst and src overlap, behavior is undefined.  Applications in
which dst and src might overlap should use memmove(3) instead. 
The memcpy() function returns the original value of dst.*/

#include "libft.h"
/*
void	*ft_memcpy(void *dst, const void *src, size_t n);

int	main(void)
{
	const int	src[] = {15, -20, 64, 87, 90};
	char		dst[] = "Hola Alejandro Vicinay";
	char		dst2[] = "Pepe Marti";
	size_t		n;
	int 		i;

	i = 0;
	while (i < 20)
	{
		printf("%d ", src[i]);
		i++;
	}
	printf("\n");
	n = 1;
	ft_memcpy(dst, src, n);
	i = 0;
	while (i < 20)
	{
		printf("%d ", dst[i]);
		i++;
	}
	memcpy(dst2, src, n);
	printf("\n");
	i = 0;
	while (i < 20)
	{
		printf("%d ", dst2[i]);
		i++;
	}
	return (0);
}
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		*((char *)(dst + i)) = *((char *)(src + i));
		i++;
	}
	return (dst);
}
