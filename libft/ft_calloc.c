/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:57 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 13:20:32 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The calloc() function contiguously allocates enough space for count
objects that are size bytes of memory each and returns a pointer to the
allocated memory.  The allocated memory is filled with bytes of value
zero*/

#include "libft.h"
/*
void	*ft_calloc(size_t count, size_t size);

int	main(void)
{
	size_t	count;
	size_t	size;
	size_t	i;
	size_t	j;

	count = 2;
	size = 10 * sizeof(char);
	i = 0;
	printf("mi funcion:");
	while (i < count * size)
	{
		printf("%d", *(char *)(ft_calloc(count, size) + i));
		i++;
	}
	printf("\noriginal:");
	j = 0;
	while (j < count * size)
	{	
		printf("%d", *(char *)(calloc(count, size) + j));
		j++;
	}
	free(ft_calloc(count, size));
	free(calloc(count, size));
	return (0);
}
*/
void	*ft_calloc(size_t count, size_t size)
{
	void		*p;
	size_t		i;	

	i = 0;
	p = malloc(count * size);
	if (p == 0)
		return ((void *)0);
	while (i < size * count)
	{
		*(char *)(p + i) = 0;
		i++;
	}
	return (p);
}
