/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:07:12 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/06 17:54:02 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_strdup("minishell> ");
	line = readline(prompt);
	while (1)
	{
		add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
		{
			free(line);
			break;
		}
		free(line);
		line = readline(prompt);
	}
	free(prompt);
	return (0);
}
