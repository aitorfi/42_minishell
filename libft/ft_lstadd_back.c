/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:48:41 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:04:22 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Añade el nodo ’new’ al final de la lista ’lst’.*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (*lst != 0)
	{
		p = ft_lstlast(*lst);
		p->next = new;
	}
	else
		*lst = new;
}
