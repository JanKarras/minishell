/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:03:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/26 21:05:41 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(void)
{
	print_error_msg("cd", "too many arguments");
	return (EXIT_FAILURE);
}

int	cd(char **args, t_env *env)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = env_value("__HOME", env);
	if (chdir(path) != 0)
	{
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	pwd = env_value("PWD", env);
	oldpwd = env_value("OLDPWD", env);
	if (oldpwd && pwd && *pwd)
		env_update("OLDPWD", pwd, env);
	if (pwd && *pwd)
		env_update("PWD", getcwd(cwd, PATH_MAX), env);
	return (EXIT_SUCCESS);
}
