/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_trim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:11:42 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/25 11:46:37 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_ret(char **ret, char *join)
{
	size_t	i;
	size_t	j;
	size_t	c;
	
	i = 0;
	c = 0;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			join[c] = ret[i][j];
			j++;
			c++;
		}
		if (ret[i][j] == 0)
		{	
			join[c] = ' ';
			c++;
		}
		i++;
	}
	printf("join: %s\n", join);
	return (join);
}

char	*increase_ret(char **ret)
{
	size_t	j;
	size_t	i;
	size_t	amount;
	char	*join;

	i = 0;
	j = 0;
	amount = 0;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			j++;
			amount++;
		}
		i++;
		amount++;
	}
	join = ft_calloc(amount + 1, 1);
	if (join == NULL)
		return (perror("malloc error while expanding $"), NULL);
	join = copy_ret(ret, join);
	return (join);
}

int	check_no_quotes(char **ret)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ret[i])
	{
		if (ret[i][0] != '\"' && ret[i][0] != '\'')
		{
			j = 0;
			while (ret[i][j] && ret[i][j] != ' ')
				j++;
			if (ret[i][j] == ' ')
				return (1);
		}
		i++;
	}
	return (0);
}

char	**exec_trim(char *arg, char **ret, size_t pos)
{
	char	*temp;

	temp = ft_strtrim(arg, "\"\'");
	if (temp == NULL)
		return (perror("malloc error  while trim"), NULL);
	free(ret[pos]);
	ret[pos] = temp;
	return (ret);
}
