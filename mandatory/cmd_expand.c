/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:46:05 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/23 15:40:44 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*search_expand(char *to_expand, t_mshell *mini_data)
{
	char	*temp;

	temp = ft_get_env(to_expand, mini_data->env_custom);
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
	return (temp);
}

static char	*exec_expand_comp(char **ast, t_mshell *mini_data, size_t pos)
{
	size_t	i;
	size_t	j;
	size_t	c;
	char	*first;
	char	*second;
	char	*to_expand;
	char	*search;
	char	*keep;
	char	*temp;
	
	j = 0;
	c = 0;
	i = 0;
	keep = NULL;
	while (1)
	{	
		i = j;
		if (keep == NULL)
		{
			while (ast[pos][i] && ast[pos][i] != '$')
				i++;
			first = ft_substr(ast[pos], 0, i);
			if (first == NULL)
				return (perror("malloc error while expanding $"), NULL);
			j = i;
			while (ast[pos][j] && ast[pos][j] != ' ' && ast[pos][j] != '\"' && ast[pos][j] != '\'')
				j++;
			to_expand = ft_substr(ast[pos], i + 1, j - i - 1);
			if (to_expand == NULL)
				return (perror("malloc error while expanding $"), NULL);
			else
			{
				search = search_expand(to_expand, mini_data);
				free(to_expand);
				if (search == NULL)
					return (NULL);
				keep = ft_strjoin(first, search);
				if (keep == NULL)
					return (perror("malloc error while expanding $"), NULL);
				free(first);
				free(search);
			}
			second = ft_substr(ast[pos], j, ft_strlen(ast[pos]) - j);
			if (second == NULL)
				return (perror("malloc error while expanding $"), NULL);
			first = keep;
			keep = ft_strjoin(keep, second);
			if (keep == NULL)
				return (perror("malloc error while expanding $"), NULL);
			free(first);
			free(second);
		}
		else
		{
			i = 0;
			i = j;
			while (keep[i] && keep[i] != '$')
				i++;
			if (!keep[i])
				break;
			first = ft_substr(keep, 0, i);
			if (first == NULL)
				return (perror("malloc error while expanding $"), NULL);
			j = i;
			while (keep[j] && keep[j] != ' ' && keep[j] != '\"' && keep[j] != '\'')
				j++;
			second = ft_substr(keep, j, ft_strlen(keep) - j);
			if (second == NULL)
				return (perror("malloc error while expanding $"), NULL);
			to_expand = ft_substr(keep, i + 1, j - i - 1);
			if (to_expand == NULL)
				return (perror("malloc error while expanding $"), NULL);
			else
			{
				search = search_expand(to_expand, mini_data);
				free(to_expand);
				if (search == NULL)
					return (NULL);
				temp = keep;
				keep = ft_strjoin(first, search);
				if (keep == NULL)
					return (perror("malloc error while expanding $"), NULL);
				free(temp);
				free(first);
				free(search);
			}
			first = keep;
			keep = ft_strjoin(keep, second);
			if (keep == NULL)
				return (perror("malloc error while expanding $"), NULL);
			free(first);
			free(second);
		}
	}
	return (keep);
}

/*ls -l | grep 'hola $que tal' $PATH 'estoy 1adios "   pepe "   adios' 2'ho'la "que $USER $USER $PWD"*/

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
	char	*new; 
	
	if (!ft_strncmp(dolar, ast[pos] + 1, ft_strlen(dolar)))
		return (exec_expand_simple(dolar, ast, mini_data, pos));
	else
	{
		new = exec_expand_comp(ast, mini_data, pos);
		if (new == NULL)
			return (NULL);
		free(ast[pos]);
		ast[pos] = new;
	}
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


/*ls -l | grep 'hola $que tal'  adios$HOMENO  hola$HOME $PATH 'estoy 1adios "   pepe "   adios' 2'ho'la "que $USER hola $USER   hola   $PWD  hola"*/