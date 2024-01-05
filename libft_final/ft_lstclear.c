/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:08:55 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 10:55:57 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Elimina y libera el nodo ’lst’ dado y todos los consecutivos de ese nodo, 
utilizando la función ’del’ y free(3).
Al final, el puntero a la lista debe ser NULL.*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst != 0)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
