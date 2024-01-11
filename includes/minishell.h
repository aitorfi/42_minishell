/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:51:51 by alejandro         #+#    #+#             */
/*   Updated: 2024/01/11 11:20:05 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef enum e_operation
{
	IN_REDIR_OP, 			// < operator
	IN_REDIR_APPEND_OP,		// << operator
	OUT_REDIR_OP,			// > operator
	OUT_REDIR_APPEND_OP,	// >> operator
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

typedef struct s_mshell
{
	char	**env_custom;
}			t_mshell;


char	**preprocess(char *line);
void	set_signal_handlers();
t_ast	**build_ast(char *line);
void	process_ast(t_ast **ast);

// modulo - Builtin -> PWD
int		do_pwd(void);

// modulo - Builtin -> CD
int		do_cd(t_mshell *mini_data, char **arguments);

// modulo aux - para inicializar y guardar las variables de entorno
//----> init_environment.c <----
char	**do_env_init(char **envp, int print);

// modulo aux - para modificiar variables entorno
//----> environment_utils.c <----
char	*ft_get_env(char *env_to_get, char **envp);
int		ft_update_env(char	*new_content, t_mshell *mini_data, char *which);
char	*ft_set_env(char *env_to_set);
int 	ft_exec_update_env(t_mshell *mini_data, char *which, char *to_change);
void	ft_free_env(char **env_custom);

int		do_echo(char **arguments);


#endif
