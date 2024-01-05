/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:25:03 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:08:36 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Crea un nuevo nodo utilizando malloc(3). La variable miembro ’content’ se 
inicializa con el contenido del parámetro ’content’. 
La variable ’next’, con NULL.*/

#include "libft.h"
/*
t_list	*ft_lstnew(void *content);

int	main(void)
{
	int	nodo;

	nodo = 1500;
	printf("ft_lstnew: %p\n", ft_lstnew(&nodo));
	return (0);
}
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	if (list == 0)
		return (0);
	list->content = content;
	list->next = 0;
	return (list);
}
