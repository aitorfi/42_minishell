/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:01:50 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/10 11:26:56 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*set_cd_one_less(char *cwd)
{
	size_t	i;

	i = 0;
	while (cwd[i])
		i++;
	while (cwd[i] != '/' && cwd[i])
		i--;
	printf("%s\n", &cwd[i]);
	return (NULL);
}	

int	set_cd_special_case(char *cwd, char *arguments)
{
	size_t	i;
	char	*dir_to_go;

	i = 0;
	if (arguments[i] == "..")
	{
		dir_to_go = set_cd_one_less(cwd);
	}
	return (0);
}