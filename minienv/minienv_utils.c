/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:28:45 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/25 13:28:46 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(char *name, t_env *env)
{
	t_env	*aux;

	aux = env_node(name, env);
	if (!aux)
		return (NULL);
	return (value_only(aux->key));
}

t_env	*env_node(char *name, t_env *env)
{
	t_env	*aux;
	int		size;

	aux = env;
	size = ft_strlen(name);
	while (aux)
	{
		if (ft_strncmp(name, aux->key, size) == 0)
		{
			if (aux->key[size] == '=')
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	env_update(char *name, char *value, t_env *env)
{
	t_env	*aux;
	char	*new_keypair;
	int		size;
	int		i;

	aux = env_node(name, env);
	if (!aux)
	{
		new_keypair = create_keypair(name, value);
		list_append(new_keypair, &env);
		free(new_keypair);
		return ;
	}
	free(aux->key);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	new_keypair = malloc(size * sizeof(char));
	i = 0;
	while (*name)
		new_keypair[i++] = *name++;
	new_keypair[i++] = '=';
	while (*value)
		new_keypair[i++] = *value++;
	new_keypair[i] = '\0';
	aux->key = new_keypair;
}

size_t	env_size(t_env *env)
{
	size_t	size;
	t_env	*aux;

	size = 0;
	aux = env;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	aux = env;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->key);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
