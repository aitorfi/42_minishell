/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/08 19:45:44 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*replace_chars(char *str, char find, char replace);

// TODO: Esta función deberia devolver la linea recibida por parámetro lista para ser parseada al AST,
// TODO: podria devolver un puntero null en caso de que el comando no sea valido.
char	**preprocess(char *line)
{
	// TODO: Sustituir variables de entorno por su valor.

	// TODO: No interpretar caracteres especiales on especificados en el subject.
	// TODO: No estoy seguro de si deberiamos eliminar estos caracteres 
	// TODO: y continuar con la ejecución o devolver un error en caso de encontrar alguno.
	
	char	**ret;

	line = replace_chars(line, '\t', ' ');
	ret = ft_split(line, ' ');
	return (ret);
}

static char	*replace_chars(char *str, char find, char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == find)
			str[i] = replace;
		i++;
	}
	return (str);
}
