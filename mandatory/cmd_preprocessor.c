/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/17 10:59:33 by alvicina         ###   ########.fr       */
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
//////////////////////////////////////////////////////////////////////////////////
/*
static char	*replace_chars(char *str, char *to_find, char replace)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{	
		j = 0;
		while (to_find[j])
		{
			if (str[i] == to_find[j])
				str[i] = replace;
			j++;
		}
		i++;
	}
	return (str);
}

char	**preprocess(char *line)
{	
	char	**ret;
	char	*to_find;

	to_find = "\t\n\v\f\r";
	line = replace_chars(line, to_find, ' ');
	ret = ft_split(line, ' ');
	return (ret);
}

int	main(void)
{
	char	line[100] = "hola \t\v\f\r que\t\n\v\f\rtal ";
	char	**line_process;
	size_t	i;

	line_process = preprocess(line);
	i = 0;
	while (line_process[i])
	{
		printf("%s\n", line_process[i]);
		i++;
	}
	
	return (0);
}*/
