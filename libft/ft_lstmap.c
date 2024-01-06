/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:05:55 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 10:52:51 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 1) compruebo que tanto lst, f y del , no esten apuntando a NULL. 2) Creo el 
primer nodo.3) Itero el contenido del primer nodo con la funcion f. 4) Guardo 
la direccion al primer nodo en save. 5) Avanzo una posicion. 6. Genero un 
bucle que a medida que vaya recorriendo la lista original, vaya creando 
nodos de la nueva lista con el contenido de la lista original iterado con 
f. Si, en algun caso, hay problema de alocar memoria para algun nodo de la 
nueva lista, libera el espacio reservado para el contenido de cada nodo de la 
nueva lista así como para cada nodo de la nueva lista con ft_lstclear
Retornamos un puntero a la primera direccion de la nueva lista 
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*save;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	new = ft_lstnew((lst->content));
	if (new == 0)
		return (0);
	new->content = f(new->content);
	save = new;
	lst = lst->next;
	while (lst != 0)
	{
		new->next = ft_lstnew((lst->content));
		if (new->next == 0)
		{
			ft_lstclear(&save, del);
			return (0);
		}
		new = new->next;
		new->content = f(new->content);
		lst = lst->next;
	}
	new->next = 0;
	return (save);
}
