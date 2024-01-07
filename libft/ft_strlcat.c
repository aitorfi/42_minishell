/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:04:08 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:24:32 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* hay que concatenar src en dst. Dst puede tener algo ya en el, por lo que
el espacio real disponible no es dstsize, si no dstsize - el strlen de dst y 
- 1 para dejar espacio al NULL. Haciendo eso nos queda cargado en una
variable "i" el espacio real disponible. Si i > dstsize, no hay espacio
*/

#include "libft.h"
/*
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);

int	main(void)
{
	char	src[50] = "lorem ipsum dolor sit amet";
	char	dst[50] = "Alejandro";
	char	dst2[50] = "Alejandro";
	size_t	dstsize;
	size_t	x;
	int		i;

	dstsize = 0;
	x = ft_strlcat(dst, src, dstsize);
	i = -1;
	while (++i < 53)
		printf("%d ", dst[i]);
	printf("%zu x\n", x);
	x = strlcat(dst2, src, dstsize);
	i = -1;
	while (++i < 53)
		printf("%d ", dst2[i]);
	printf("%zu x", x);
	return (0);
}
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] != 0 && dstsize > i)
		i++;
	j = 0;
	if (i < dstsize)
	{
		while (i < dstsize - 1 && src[j] != 0)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = 0;
	}
	while (src[j] != 0)
	{
		j++;
		i++;
	}
	return (i);
}
