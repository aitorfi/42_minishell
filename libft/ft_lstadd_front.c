/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:35:43 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:07:26 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Añade el nodo ’new’ al principio de la lista ’lst’*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
