/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:21 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/24 19:32:45 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_str(t_env *env)
{
	char		*user;
	char		*cwd;
	char		*directory;
	static char	prompt[PATH_MAX];

	user = env_value("USER", env);
	if (!user)
		user = "UNKNOWN";
	cwd = env_value("PWD", env);
	if (!cwd)
		cwd = "/UNKNOWN";
	directory = ft_strrchr(cwd, '/') + 1;
	if (ft_strncmp(cwd, "/", 2) == 0)
		directory = "ROOT";
	ft_bzero(prompt, sizeof(prompt));
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, "@", PATH_MAX);
	ft_strlcat(prompt, directory, PATH_MAX);
	return (prompt);
}

char	*prompt_input(t_env *env)
{
	char	*input;

	input = readline(get_prompt_str(env));
	if (!input)
		builtin_exit(NULL, &env);
	if (input && *input)
		add_history(input);
	return (input);
}
