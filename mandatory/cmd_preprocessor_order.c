/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:28:28 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/29 12:29:25 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**exec_order(char **ret, char **temp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ret[i])
	{
		if (*ret[i] == 0)
			i++;
		else
		{
			temp[j] = ft_strdup(ret[i]);
			if (temp[j] == NULL)
				return (NULL);
			j++;
			i++;
		}
		if (!ret[i])
			break ;
	}
	if (!ret[i])
		temp[j] = NULL;
	return (temp);
}

char	**order_args(char	**ret)
{
	size_t	i;
	size_t	amount;
	char	**temp;

	i = 0;
	amount = 0;
	while (ret[i])
	{
		if (*ret[i] == 0)
			i++;
		else
		{
			amount++;
			i++;
		}
	}
	temp = malloc(sizeof(char *) * (amount + 1));
	if (temp == NULL)
		return (NULL);
	temp = exec_order(ret, temp);
	if (temp == NULL)
		return (NULL);
	ft_free_env(ret);
	return (temp);
}
