/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:17:33 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/14 12:11:55 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_export(char **env_to_export)
{
	size_t	i;
	char	*temp;
	size_t	len_to_compare;

	i = 0;
	while (env_to_export[i] && env_to_export[i + 1])
	{
		len_to_compare = compare_lens(env_to_export[i], env_to_export[i + 1]);
		if (env_to_export[i + 1] && ft_strncmp(env_to_export[i + 1],
				env_to_export[i], len_to_compare) < 0)
		{
			temp = env_to_export[i];
			env_to_export[i] = env_to_export[i + 1];
			env_to_export[i + 1] = temp;
		}
		i++;
	}
}

int	check_sort_export(char **env_to_export)
{
	size_t	i;
	size_t	len_to_compare;

	i = 0;
	len_to_compare = 0;
	while (env_to_export[i] && env_to_export[i + 1])
	{
		len_to_compare = compare_lens(env_to_export[i], env_to_export[i + 1]);
		if (env_to_export[i + 1] && ft_strncmp(env_to_export[i + 1],
				env_to_export[i], len_to_compare) < 0)
			return (1);
		i++;
	}
	return (0);
}
