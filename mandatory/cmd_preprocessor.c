/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/17 18:15:36 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **get_double(char *line, size_t d_quote, char c)
{
	char	**where_double;
	size_t	i;
	size_t	j;
	
	where_double = malloc(sizeof(char *) * (d_quote + 1));
	if (where_double == NULL)
		return (ft_putstr_fd("could not process line\n", 2), g_result = 1, NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			printf("%c\n", line[i]);
			where_double[j++] = &line[i++];
		}
		i++;
	}
	where_double[j] = NULL;
	//i = 0;
	//while (where_double[i])
	//{
	//	printf("%p\n", where_double[i]);
	//	i++;
	//}
	return (where_double);
}

static void print_error_double_quote(void)
{
	g_result = 1;
	ft_putstr_fd("minishell> unexpected EOF while looking for matching \"\n", 2);
	exit(g_result);
}

static int check_quote(char *line, char c)
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
		print_error_double_quote();
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
	size_t	double_quote;
	size_t	single_quote;
	char	**where_double;
	
	where_double = NULL;
	line = replace_chars(line, "\t\n\v\f\r", ' ');
	double_quote = check_quote(line, '\"');
	if (double_quote)
	{
		where_double = get_double(line, double_quote, '\"');
		if (where_double == NULL)
			return (NULL);
	}
	single_quote = check_quote(line, '\'');
	ret = ft_split(line, ' ');
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
