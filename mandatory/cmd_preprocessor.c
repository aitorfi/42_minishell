/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/07 10:45:25 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Esta función deberia devolver la linea recibida por parámetro lista para ser parseada al AST,
// TODO: podria devolver un puntero null en caso de que el comando no sea valido.
char	*preprocess(char *line)
{
	(void) line; // Esto es para que no de error de parámetro sin usar.
	// TODO: Sustituir variables de entorno por su valor.

	// TODO: No interpretar caracteres especiales on especificados en el subject.
	// TODO: No estoy seguro de si deberiamos eliminar estos caracteres 
	// TODO: y continuar con la ejecución o devolver un error en caso de encontrar alguno.
	return (line);
}
