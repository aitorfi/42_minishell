/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:51:51 by alejandro         #+#    #+#             */
/*   Updated: 2024/01/20 14:25:47 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

int	g_result;

typedef enum e_ast_node_type
{
	ROOT = 0,
	LEFT,
	RIGHT	
}	t_ast_node_type;

typedef enum e_operation
{
	IN_REDIR_OP	= 1,		// < operator
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

typedef struct s_mshell
{
	char	**env_custom;
	int		stdout_fd;
}			t_mshell;

typedef struct s_preprocess
{
	size_t	init;
	size_t	count;
	size_t	final;
	size_t	limit;
	int		flag;
	char	quote;
	size_t	start;
	size_t	end;
}			t_preprocess;

// sig_handler:
void		set_signal_handlers(void);

// cmd_preprocessor:
char		**preprocess(char *line);

// cmd_split_preprocess
char	**ft_split_preprocess(char const *s, char c);

// cmd_split_preprocess_utils
void	d_init(t_preprocess *d);
char	**ft_free_split_preprocess(char **split, size_t limit);
void 	print_error_quote(int c);

// ast_builder:
t_ast	**build_ast(char **args, t_mshell *mshell);

// heredoc:
char		*create_heredoc(char *limit);

// ast_processor:
void		process_ast(t_ast **ast, t_mshell *mshell);

// utils:
t_operation	which_operator(char *operator);
char		*which_operator_str(t_operation operator);
char		*append_path_to_cmd(char **envp, char *cmd);

// error_utils:
void		*free_massive(void *ptr, ...);
int			free_massive_exit_failure(void *ptr, ...);
void		*free_split(char **split);
int			notify_error(char *msg);
void		*notify_error_ptr(char *msg);

// file_utils:
char		*create_file(char *path, char *content);
char		*get_file_content_fd(int fd);
char		*get_file_content(char *path);
int			close_massive(int fd, ...);

// ast_utils:
void		*free_ast(t_ast **ast);
void		*free_ast_node(t_ast *node);
void		print_ast(t_ast *node, int depth);
t_ast		*new_node(t_operation op, char *path, char **args, char *limit);

// builtin_utils:
int			is_builtin(char *cmd);
int			execute_builtin(t_ast *node, t_ast_node_type type, int *rfd, int *wfd, t_mshell *mshell);

// builtin_pwd:
int			do_pwd(void);

// builtin_cd:
int			do_cd(t_mshell *mini_data, char **arguments);

// builtin_echo:
int			do_echo(char **arguments);

// builtin_env:
int			execute_env(char **environment);

// builtin_export:
int			do_export(t_mshell *mini_data, char **arguments);
int			check_export_args(char *arguments);

// builtin_export_sort:
int			check_sort_export(char **env_to_export);
void		sort_export(char **env_to_export);

// builtin_export_utils:
size_t		compare_lens(char *s1, char *s2);
void		print_export(char **env_to_export);
void		print_error_export(char *arguments);
int			change_export_env(t_mshell *mini_data, char *arguments, size_t pos);
int			add_export_env(t_mshell *mini_data, char *arguments);

// builtin_exit
int			do_exit(char **arguments);

// builtin_exit_utils
void		check_exit_args(char **arguments, int *flag);
int			ft_atoi_exit(char *str);
int			is_number(char *arguments);
void		do_exit_atoi(char *arguments);

// builtin_unset:
int			do_unset(t_mshell *mini_data, char **arguments);

// // builtin_unset_utils:
void	print_error_unset(char *arguments);
int		check_unset_args(char *arguments);


// init_environment:
// Modulo auxiliar para inicializar y guardar las variables de entorno
char		**do_env_init(char **envp, int print);

// environment_utils: Modulo auxiliar para modificar variables de entorno
char		*ft_get_env(char *env_to_get, char **envp);
int			ft_update_env(char	*new_content, t_mshell *mini_data, char *which);
char		*ft_set_env(char *env_to_set);
int			ft_exec_update_env(
				t_mshell *mini_data, char *which, char *to_change);
void		ft_free_env(char **env_custom);
#endif
