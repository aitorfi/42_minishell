/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:46:05 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/22 13:29:21 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_expand(char *ret)
{
	
}

static int	check_dollar(char *ret)
{
	size_t	i;

	i = 0;
	while(ret[i])
	{
		if (ret[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	check_expand(char *ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		if (ret[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

int	do_expand(char **ret)
{
	size_t	i;
	
	i = 0;
	while (ret[i])
	{
		if (check_expand(ret[i]))
		{
			if(check_dollar(ret[i]))
			{
				printf("******tiene DOLLAR*******%s\n", ret[i]);
				exec_expand(ret[i]);
			}
		}
		i++;	
	}
	return (0);
}


/*ls -l | grep \'hola $que tal\' $aqui \'estoy 1adios \"   pepe \"   adios\' 2\'ho\'la \"que $tal\"*/