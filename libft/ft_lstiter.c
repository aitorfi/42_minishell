/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:59:56 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 10:53:47 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Iteramos el contenido de una lista con la funcion f*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != 0)
	{
		f(lst->content);
		lst = lst->next;
	}
}
