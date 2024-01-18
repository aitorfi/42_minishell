/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/18 12:24:00 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int get_quote(char *line, size_t d_quote, char c, char ***where_quote)
{
	size_t	i;
	size_t	j;
	char	**temp;
	
	temp = malloc(sizeof(char *) * (d_quote + 1));
	if (temp == NULL)
		return (ft_putstr_fd("could not process line\n", 2), g_result = 1, 1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			printf("%c\n", line[i]);
			temp[j++] = &line[i++];
		}
		i++;
	}
	temp[j] = NULL;
	*where_quote = temp;
	return (0);
}

static void print_error_quote(int c)
{
	g_result = 1;
	if (c == '\"')
		ft_putstr_fd("minishell> unexpected EOF while looking for matching \"\n", 2);
	else
		ft_putstr_fd("minishell> unexpected EOF while looking for matching \'\n", 2);
	exit(g_result);
}

static size_t check_quote(char *line, char c)
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
	if (d_quote % 2 != 0)
		print_error_quote(c);
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

static int	quote(char *line, int c, char ***where_quote)
{
	size_t	quote;

	quote = check_quote(line, c); 
	if (quote)
	{
		 if (get_quote(line, quote, c, where_quote))
			return (1);
		return (0);
	}
	return (0);
}

char	**preprocess(char *line)
{	
	char	**ret;
	char	**where_double;
	char	**where_single;
	
	where_double = NULL; //hay que liberar
	where_single = NULL; //hay que liberar
	ret = NULL;
	line = replace_chars(line, "\t\n\v\f\r", ' ');
	if (quote(line, '\"', &where_double))
		return (NULL);
	if (quote(line, '\'', &where_single))
		return (NULL);
	// hay que meter funcion para comparar si hay una doble dentro de dos simples y al reves
	ret = ft_split_preprocess(line, ' '); // hay que liberar
	if (ret == NULL)
		return (NULL);
	return (ret);
}

int	main(void)
{
	//char	line[100] = "hola \t\v\f\r que\t\n\v\f\rtal ";
	char	*line;
	//char	**line_process;
	size_t	i;

	//while (1)
	//{
		line = readline("minishell> ");
		preprocess(line);
		i = 0;
		/*while (line_process[i])
		{
			printf("%s\n", line_process[i]);
			i++;
		}*/
		//ft_free_env(line_process);
		//free(line);
	//}
	return (0);
}
