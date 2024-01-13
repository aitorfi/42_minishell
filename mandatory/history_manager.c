/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorfi <aitorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:35:36 by aitorfi           #+#    #+#             */
/*   Updated: 2024/01/13 13:39:37 by aitorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_heredoc_to_history(char *line, t_ast **ast);

int	handle_history(char *line, t_ast **ast)
{
	if (ast[0] && ast[0]->operation == IN_REDIR_APPEND_OP)
		return (add_heredoc_to_history(line, ast));
	else
		add_history(line);
	return (EXIT_SUCCESS);
}

static int	add_heredoc_to_history(char *line, t_ast **ast)
{
	int		fd;
	char	*content;

	fd = open(ast[0]->right->path, O_RDONLY);
	if (fd == -1)
		return (notify_error("Error"));
	content = get_file_content(fd);
	if (content == NULL)
	{
		printf("content error\n");
		close(fd);
		return (EXIT_FAILURE);
	}

	printf("content = %s\n", content);
	printf("line = %s\n", line);

	close(fd);
	add_history(ft_strjoin(line, content));
	free(content);
	return (EXIT_SUCCESS);
}
