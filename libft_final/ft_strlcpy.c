/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:44:40 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/05 17:24:42 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*strlcpy() copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.Return value for strlcpy() 
that means the length of src.*/

#include "libft.h"
/*
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);

int	main(void)
{
	char	src[30] = "Hola Alejandro Vicinay";
	char	dst[30];
	char	dst2[30];
	size_t	dstsize;
	size_t	x;
	int		i;

	dstsize = 30;
	x = ft_strlcpy(dst, src, dstsize);
	i = -1;
	while (++i < 35)
		printf("%d ", dst[i]);
	printf("%zu x", x);
	printf("\n");
	x = strlcpy(dst2, src, dstsize);
	i = -1;
	while (++i < 35)
		printf("%d ", dst2[i]);
	printf("%zu x", x);
	return (0);
}
*/
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1)
		{
			if (src[i] == 0)
				break ;
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	i = 0;
	while (src[i] != 0)
		i++;
	return (i);
}
