/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/22 10:53:59 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	check_quote(char *line, char c)
{
	size_t	i;
	size_t	d_quote;

	i = 0;
	d_quote = 0;
	while (line[i])
	{
		if (line[i] == c)
			d_quote++;
		i++;
	}
	return (d_quote);
}

static char	*replace_chars(char *str, char *to_find, char replace)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j])
		{
			if (str[i] == to_find[j])
				str[i] = replace;
			j++;
		}
		i++;
	}
	return (str);
}

char	**preprocess(char *line)
{
	char	**ret;
	size_t	single_quote;
	size_t	double_quote;

	ret = NULL;
	line = replace_chars(line, "\t\n\v\f\r", ' ');
	single_quote = check_quote(line, '\'');
	double_quote = check_quote(line, '\"');
	ret = ft_split_preprocess(line, ' ');
	if (ret == NULL)
		return (NULL);
	do_expand(ret);
	return (ret);
}

int	main(void)
{
	//char	line[100] = "hola \t\v\f\r que\t\n\v\f\rtal ";
	char	*line;
	char	**line_ast;
	size_t	i;

	
	i = 0;
	line = readline("minishell> ");
	line_ast = preprocess(line);
	while (line_ast[i])
	{
		printf("%s\n", line_ast[i]);
		i++;
	}
	ft_free_env(line_ast);
	free(line);
	return (0);
}

