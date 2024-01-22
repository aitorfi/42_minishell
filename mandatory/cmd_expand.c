/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:46:05 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/22 19:53:46 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**exec_expand_comp(char *dolar, char **ast, t_mshell *mini_data, size_t pos)
{
	size_t	i;
	size_t	j;
	size_t	c;
	char	*first;
	char	*to_expand;
	//char	third;
	
	i = 0;
	j = 0;
	c = 0;
	(void) dolar;
	(void) mini_data;
	while (ast[pos][i])
	{	i = j;
		while (ast[pos][i] && ast[pos][i] != '$')
			i++;
		first = ft_substr(ast[pos], 0, i);
		if (first == NULL)
			return (perror("malloc error while expanding $"), NULL);
		printf("first: %s\n", first);
		j = i;
		while (ast[pos][j] && ast[pos][j] != ' ')
			j++;
		to_expand = ft_substr(ast[pos], i + 1, j);
		if (to_expand == NULL)
			return (perror("malloc error while expanding $"), NULL);
		else
		{
			//////tengo que buscar variable y la hay, expandir, y luego strjoin/////////
		}
		i = j;
		printf("second: %s\n", second);
	}
	return (NULL);
}

static char	**exec_expand_simple(char *dolar, char **ast, t_mshell *mini_data, size_t pos)
{
	char	*temp;
	
	temp = ft_get_env(dolar, mini_data->env_custom);
	if (temp == NULL)
	{
		temp = ft_strdup("");
		if (temp == NULL)
			return (perror("malloc error while expanding $"), NULL);
	}
	else
	{
		temp = ft_set_env(temp);
		temp = ft_strdup(temp);
		if (temp == NULL)
			return (perror("malloc error while expanding $"), NULL);
	}
	free(ast[pos]);
	ast[pos] = temp;
	return (ast);
}

static char **exec_expand(char *dolar, char **ast, t_mshell *mini_data, size_t pos)
{
	if (!ft_strncmp(dolar, ast[pos] + 1, ft_strlen(dolar)))
		return (exec_expand_simple(dolar, ast, mini_data, pos));
	else
		return (exec_expand_comp(dolar, ast, mini_data, pos));
	return (0);
}

static char	*check_dollar(char *ret)
{
	size_t	i;

	i = 0;
	while(ret[i])
	{
		if (ret[i] == '$')
		{
			i++;
			return (&ret[i]);
		}
		i++;
	}
	return (NULL);
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

int	do_expand(char **ret, t_mshell *mini_data)
{
	size_t	i;
	char	*where_$;
	
	i = 0;
	while (ret[i])
	{
		if (check_expand(ret[i]))
		{
			where_$ = check_dollar(ret[i]);
			if(where_$)
				exec_expand(where_$, ret, mini_data, i);
		}
		i++;	
	}
	i = 0;
	while (ret[i])
	{
		printf("cambiados: %s\n", ret[i]);
		i++;
	}
	return (0);
}


/*ls -l | grep \'hola $que tal\' $PATH \'estoy 1adios \"   pepe \"   adios\' 2\'ho\'la \"que $tal\"*/