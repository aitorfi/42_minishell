/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:51:51 by alejandro         #+#    #+#             */
/*   Updated: 2024/01/14 11:27:12 by afidalgo         ###   ########.fr       */
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
	char			*limit;
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
int			free_massive_exit_failure(void *ptr, ...);
void		*free_split(char **split);
char		*create_file(char *path, char *content);
void		*free_ast(t_ast **ast);
void		*free_ast_node(t_ast *node);
void		print_ast(t_ast *node, int depth);
t_ast		*new_node(t_operation op, char *path, char **args, char *limit);
char		*create_heredoc(char *limit);
int			handle_history(char *line, t_ast **ast);
int			notify_error(char *msg);
void		*notify_error_ptr(char *msg);
char		*get_file_content_fd(int fd);
char		*get_file_content(char *path);
#endif
