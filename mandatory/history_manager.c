/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:35:36 by aitorfi           #+#    #+#             */
/*   Updated: 2024/01/14 11:28:22 by afidalgo         ###   ########.fr       */
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
	char	*content;
	char	*del;
	char	*hist;

	content = get_file_content(ast[0]->right->path);
	if (content == NULL)
		return (EXIT_FAILURE);
	hist = ft_strjoin(line, "\n");
	if (hist == NULL)
		return (free_massive_exit_failure(content));
	del = hist;
	hist = ft_strjoin(hist, content);
	free_massive(del, content);
	if (hist == NULL)
		return (EXIT_FAILURE);
	del = hist;
	hist = ft_strjoin(hist, ast[0]->right->limit);
	free(del);
	if (hist == NULL)
		return (EXIT_FAILURE);
	add_history(hist);
	return (EXIT_SUCCESS);
}
