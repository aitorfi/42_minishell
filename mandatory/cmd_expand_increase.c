/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_increase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:11:42 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/25 13:13:27 by alvicina         ###   ########.fr       */
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
/*
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
*/
char	**increase_routine(char **ret)
{
	char	**temp;
	char	*join;

	//if (check_no_quotes(ret))
	//{
		temp = ret;
		join = increase_ret(ret);
		if (join == NULL)
			return (perror("malloc error while expanding $"), NULL);
		ft_free_env(temp);
		ret = ft_split_preprocess(join, ' ');
		if (ret == NULL)
			return (perror("malloc error while expanding $"), NULL);
		free(join);
	//}
	return (ret);
}
