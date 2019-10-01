/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_trim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:11:42 by alvicina          #+#    #+#             */
/*   Updated: 2019/10/01 02:00:18 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**exec_trim(char *arg, char **ret, size_t pos)
{
	char	*temp;

	temp = ft_strtrim(arg, "\"\'");
	if (temp == NULL)
		return(perror("malloc error  while trim"), NULL);
	free(ret[pos]);
		
}