/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:39:45 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:01:02 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Toma como parámetro un nodo ’lst’ y libera la memoria del contenido 
utilizando la función ’del’ dada como parámetro, además de liberar el nodo. 
La memoria de ’next’ no debe liberarse.*/

#include "libft.h"

void	ft_lstdelone(t_list *list, void (*del)(void *))
{
	del(list->content);
	free (list);
}
