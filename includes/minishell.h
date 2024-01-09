/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:51:51 by alejandro         #+#    #+#             */
/*   Updated: 2024/01/09 18:11:32 by alvicina         ###   ########.fr       */
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
int		do_pwd(void);
char	**do_env(char **envp, int print);
void	ft_free_env(char **env_custom);
char	*ft_get_env(char *env_to_get, char **envp);
int		do_cd(t_mshell *mini_data, char **arguments);
int		ft_update_env(char	*new_content, t_mshell *mini_data, char *which);
char	*ft_set_env(char *env_to_set);

#endif
