/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:37:55 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/11 10:40:39 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// NOTA: getcwd asigna memoria dinamica. Hay que hacer free al retorno una vez
// no haga fala.
// NOTA: de momento este modulo imprime y libera el resultado. Tal vez podriamos
// necesitar que devolviera el resultado para este ser gestionado 
//(imprimido y liberado) desde otro lugar;

static void	print_pwd(char *cw_directory)
{
	write(1, cw_directory, ft_strlen(cw_directory));
	write(1, "\n", 1);
}

int	do_pwd(void)
{
	char	*cw_directory;

	cw_directory = getcwd(NULL, 0);
	if (cw_directory == NULL)
	{
		perror("cwd could not be found");
		return (1);
	}
	else
	{
		print_pwd(cw_directory);
		free(cw_directory);
		return (0);
	}
}
/*
int	main(void)
{
	do_pwd();
	return (0);
}
*/