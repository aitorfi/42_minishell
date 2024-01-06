/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:26:29 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 17:41:40 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The memset() function writes len bytes of value c (converted to an
unsigned char) to the string b.*/

#include "libft.h"
/*
void	*ft_memset(void *b, int c, size_t len);

int	main(void)
{
	char	b[] = "Hola Alejandro Vicinay";
	char	c;
	size_t	len;

	c = 'a';
	len = 5;
	ft_memset(b, c, len);
	printf("%s ft\n", b);
	memset(b, c, len),
	printf("%s or\n", b);
	return (0);
}
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((char *)(b + i)) = c;
		i++;
	}
	return (b);
}
