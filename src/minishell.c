/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/24 14:16:15 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_env *env)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		define_main_signals();
		input = prompt_input(env);
		if (has_input_error(input, &exit_status, env))
			continue ;
		handle_expansions(&input, env, exit_status);
		if (!has_pipe(input))
			exit_status = execute_one_command(input, &env);
		else
		{
			commands = split_commands(input);
			free(input);
			exit_status = execute_multiple_commands(commands, &env);
			free_array(commands);
		}
	}
	return (exit_status);
}
