/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:37:25 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/11 12:35:58 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// NOTA: // NOTA: do_env asigna memoria dinamica para el puntero al array de 
// punteros y para los strings a los que apuntan dichos punteros.
// Hay que hacer free una vez no hagan falta las variables de entorno.
// Para ello he creado la funcion ft_free_env que libera la memoria 
// dinamica asignada.
// NOTA: de momento este modulo NO imprime (aunque puede si se le pasa
// un valor - int print - != 0) y NO libera el resultado 
// ya que nos hara falta durante la ejecucion del programa.

static void	print_env_init(char **env_custom)
{
	size_t	i;

	i = 0;
	while (env_custom[i])
	{
		write(1, env_custom[i], ft_strlen(env_custom[i]));
		write(1, "\n", 1);
		i++;
	}
}

static char	**get_env_init(char **env_custom, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		env_custom[i] = ft_strdup(envp[i]);
		if (env_custom[i] == NULL)
		{
			ft_free_env(env_custom);
			return (NULL);
		}
		i++;
	}
	env_custom[i] = NULL;
	return (env_custom);
}

static char	**set_env_init(char **envp)
{
	size_t	i;
	char	**env_custom;

	i = 0;
	while (envp[i])
		i++;
	env_custom = malloc(sizeof(char *) * (i + 1));
	if (env_custom == NULL)
		return (NULL);
	else
		return (env_custom);
}

char	**do_env_init(char **envp, int print)
{
	char	**env_custom;

	env_custom = set_env_init(envp);
	if (env_custom == NULL)
	{
		perror("env could not be found");
		return (NULL);
	}
	env_custom = get_env_init(env_custom, envp);
	if (env_custom == NULL)
	{
		perror("env could not be found");
		return (NULL);
	}
	if (print)
		print_env_init(env_custom);
	return (env_custom);
}

/*
int	main(int argc, char **argv, char **envp)
{
	size_t	i;
	char	**env_custom;

	i = 0;
	(void) argc;
	(void) argv;
	env_custom = do_env(envp);
	ft_free_env(env_custom);
	return (0);
}*/