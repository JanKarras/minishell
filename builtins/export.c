/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:06 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/24 19:30:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	declare_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name_only(aux->key), STDOUT_FILENO);
		if (ft_strchr(aux->key, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(value_only(aux->key), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	builtin_export(char **args, t_env **env)
{
	char	*key;
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*env));
	while (*args)
	{
		key = *args;
		varname = name_only(key);
		if (!is_valid_varname(varname) || str_equal(key, "="))
		{
			print_varname_error_msg("export", key);
			exit_status = EXIT_FAILURE;
		}
		else if (env_node(varname, *env))
			env_update(varname, value_only(key), *env);
		else
			list_append(key, env);
		free(varname);
		args++;
	}
	return (exit_status);
}
