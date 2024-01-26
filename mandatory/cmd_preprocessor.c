/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/26 17:16:15 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**exec_trim(char **ret)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (ret[i])
	{
		temp = ft_strtrim(ret[i], "\"\'");
		if (temp == NULL)
			return (perror("malloc error  while trim"), NULL);
		free(ret[i]);
		ret[i] = temp;
		i++;
	}
	return (ret);
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

char	**preprocess(char *line, t_mshell *mini_data)
{
	char		**ret;

	ret = NULL;
	line = replace_chars(line, "\t\n\v\f\r", ' ');
	ret = ft_split_preprocess(line, ' ');
	if (ret == NULL)
		return (NULL);
	ret = do_expand(ret, mini_data);
	if (ret == NULL)
		return (perror("malloc error while expanding $"), NULL);
	ret = exec_trim(ret);
	if (ret == NULL)
		return (perror("malloc error while trim $"), NULL);
	return (ret);
}
/*
int	main(int argc, char **argv, char **envp)
{
	//char	line[100] = "hola \t\v\f\r que\t\n\v\f\rtal ";
	char		*line;
	char		**line_ast;
	size_t		i;
	t_mshell	mini_data;
	char		*arguments[4];

	arguments[0] = "export";
	arguments[1] = "ALE=1hola 2que 3tal";
	arguments[2] = NULL;
	arguments[3] = NULL;
	(void) argc;
	(void) argv;
	i = 0;
	mini_data.env_custom = do_env_init(envp, 0);
	do_export(&mini_data, arguments);
	//while (mini_data.env_custom[i])
	//{
	//	printf("%s\n", mini_data.env_custom[i]);
	//	i++;
	//}
	line = readline("minishell> ");
	line_ast = preprocess(line, &mini_data);
	i = 0;
	while (line_ast[i])
	{
		printf("%s\n", line_ast[i]);
		i++;
	}
	ft_free_env(line_ast);
	ft_free_env(mini_data.env_custom);
	free(line);
	//system("leaks a.out");
	return (0);
}*/
