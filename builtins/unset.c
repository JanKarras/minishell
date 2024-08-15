/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:17 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/22 15:37:58 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_from_env(char *varname, t_env **env);
static void	env_del_next_node(t_env **node);

int	unset(char **args, t_env **env)
{
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (0);
	while (*args)
	{
		varname = *args;
		if (!is_valid_varname(varname))
		{
			print_varname_error_msg("unset", varname);
			exit_status = EXIT_FAILURE;
		}
		else
			remove_from_env(varname, env);
		args++;
	}
	return (exit_status);
}

static void	remove_from_env(char *varname, t_env **env)
{
	t_env	*aux;

	aux = *env;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->key, varname, ft_strlen(varname)) == 0)
		{
			if ((aux->next)->key[ft_strlen(varname)] == '=')
				return (env_del_next_node(&aux));
		}
		aux = aux->next;
	}
}

static void	env_del_next_node(t_env **node)
{
	t_env	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->key);
	free(temp);
}
