/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:51:51 by alejandro         #+#    #+#             */
/*   Updated: 2024/01/12 18:15:15 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

# define OPERATOR_MAX_LEN 2

typedef enum e_operation
{
	IN_REDIR_OP = 1, 		// < operator
	IN_REDIR_APPEND_OP,		// << operator
	OUT_REDIR_OP,			// > operator
	OUT_REDIR_APPEND_OP,	// >> operator
	PIPE_OP,
	COMMAND_OP,
	FILE_OP
}	t_operation;

typedef struct s_ast
{
	t_operation		operation;
	char			*path;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

char		**preprocess(char *line);
void		set_signal_handlers();
t_ast		**build_ast(char **args);
void		process_ast(t_ast **ast);
int			do_pwd(void);
char		**do_env(char **envp);
void		ft_free_env(char **env_custom);
t_operation	which_operator(char *operator);
char		*which_operator_str(t_operation operator);
void		*free_massive(void *ptr, ...);
void		*free_split(char **split);
char		*create_file(char *path, char *content);
void		*free_ast(t_ast *node);
void		*free_ast_node(t_ast *node);
void		print_ast(t_ast *node, int depth);
t_ast		*new_node(t_operation op, char *path, char **args);
t_ast		*new_command_node(char *command);
char		*create_heredoc(char *limit);
#endif
