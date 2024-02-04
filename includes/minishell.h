/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:51:51 by alejandro         #+#    #+#             */
/*   Updated: 2024/02/04 13:47:10 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <errno.h>
# include "../libft/libft.h"

# define DEFAULT_FD -2
# define MSH_ERROR 2

extern int	g_result;

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
	struct s_ast	*parent;
}					t_ast;

typedef struct s_mshell
{
	char	**env_custom;
	int		stdout_fd;
	int		stdin_fd;
	t_ast	**ast;
	char	*heredoc_path;
}			t_mshell;

typedef struct s_preprocess
{
	size_t	init;
	size_t	count;
	size_t	final;
	size_t	limit;
	size_t	flag;
	char	quote;
	char	**s;
	size_t	start;
	size_t	end;
}			t_preprocess;

typedef struct s_expand
{
	size_t	i;
	size_t	j;
	size_t	result;
	size_t	flag;
	char	*first;
	char	*second;
	char	*to_expand;
	char	*search;
	char	*keep;
	char	*temp;
}			t_expand;

typedef struct s_trim
{
	size_t	i;
	size_t	j;
	size_t	c;
	char	*temp;
	char	char_q;
}			t_trim;

// sig_handler:
void		set_signal_handlers(void);
void		set_signal_handlers_fork(void);
void		set_signal_handlers_builtin(void);

// sig_handler_utils: 
void		ft_signal_father(int signal);
void		ft_signal_child(int signal);
void		ft_signal_child_builtin(int signal);

// cmd_preprocessor:
char		**preprocess(char *line, t_mshell *mini_data);

// cmd_split_preprocess:
char		**ft_split_preprocess(char const *s, char c);

// cmd_split_preprocess_utils:
void		d_init(t_preprocess *d);
char		**ft_free_split_preprocess(char **split, size_t limit);
void		print_error_quote(int c);

// cmd_expand:
char		**do_expand(char **ret, t_mshell *mini_data);

// cmd_expand utils:
int			check_expand(char *ret);
char		*check_dollar(char *ret);
void		d_expand_init(t_expand *d);
char		*search_expand(char *to_expand, t_mshell *mini_data);
char		*get_dollar_question(void);

//cmd_expand_increase:
char		*increase_ret(char **ret);
char		*copy_ret(char **ret, char *join);
char		**increase_routine(char **ret);
void		find_dollar(t_expand *d);

// ast_builder:
int			build_ast(t_ast **ast, char **args, t_mshell *mshell);

// ast_builder_nodes:
t_ast		*get_left_node(char **args, int index, t_mshell *mshell);
t_ast		*get_right_node_command(char **args, int index, t_mshell *mshell);
t_ast		*get_right_node_heredoc(char **args, int index, t_mshell *mshell);

// heredoc:
char		*create_heredoc(char *limit, t_mshell *mshell);
char		*get_heredoc_path(char **envs);

// ast_processor:
int			process_ast(t_ast **ast, t_mshell *mshell);

// ast_processor_cmd:
int			read_ast_node_command(
				t_ast *node, int rfd, int wfd, t_mshell *mshell);

// utils:
t_operation	which_operator(char *operator);
char		*which_operator_str(t_operation operator);
int			max_of(int num1, int num2);
int			split_len(char **split);
int			is_terminating_cmd(t_ast **ast);

// cmd_utils:
char		*append_path_to_cmd(char **envp, char *cmd);
int			is_builtin(char *cmd);
int			execute_builtin(t_ast *node, t_mshell *mshell, int is_main_process);

// error_utils:
void		*free_massive(void *ptr, ...);
int			free_massive_exit_failure(void *ptr, ...);
void		*free_split(char **split);
int			notify_error(char *msg);
void		*notify_error_ptr(char *msg);

// file_utils:
char		*create_file(char *path, char *content, mode_t mode);
char		*get_file_content_fd(int fd);
char		*get_file_content(char *path);
int			close_massive(int fd, ...);

// ast_utils:
void		*free_ast(t_ast **ast);
int			free_ast_status(t_ast **ast, int status);
void		*free_ast_node(t_ast *node);
t_ast		*new_node(t_operation op, char *path, char **args, char *limit);

// builtin_pwd:
int			do_pwd(void);

// builtin_cd:
int			do_cd(t_mshell *mini_data, char **arguments);

// builtin_cd_utils:
char		*set_cd_special_case(
				char *cwd, char *arguments, t_mshell *mini_data);
char		*set_cd_one_up(char *cwd);

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
int			do_exit(char **arguments, int is_main_process);
int			can_do_exit(char **arguments);

// builtin_exit_utils
void		check_exit_args(char **arguments, int *flag);
int			ft_atoi_exit(char *str, int is_main_process);
int			is_number(char *arguments);
int			do_exit_atoi(char *arguments, int is_main_process);

// builtin_unset:
int			do_unset(t_mshell *mini_data, char **arguments);

// builtin_unset_utils:
void		print_error_unset(char *arguments);
int			check_unset_args(char *arguments);

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
