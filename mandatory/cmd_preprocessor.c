/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/17 11:09:46 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	*to_find;

	to_find = "\t\n\v\f\r";
	line = replace_chars(line, to_find, ' ');
	ret = ft_split(line, ' ');
	return (ret);
}

int	main(void)
{
	//char	line[100] = "hola \t\v\f\r que\t\n\v\f\rtal ";
	char	*line;
	char	**line_process;
	size_t	i;

	//while (1)
	//{
		line = readline("minishell>");
		line_process = preprocess(line);
		i = 0;
		while (line_process[i])
		{
			printf("%s\n", line_process[i]);
			i++;
		}
		ft_free_env(line_process);
		free(line);
	//}
	return (0);
}
