/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:17:08 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/22 17:34:16 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	struct s_env	*next;
}				t_env;

t_env		*init_env(char **envp);
t_env		*env_node(char *name, t_env *env);
char		*env_value(char *name, t_env *env);
void		env_update(char *name, char *value, t_env *env);
void		list_append(char *key, t_env **list);
char		**env_to_envp(t_env *env);
void		free_env(t_env **env);
char		*create_keypair(char *name, char *value);
char		*name_only(char *key);
char		*value_only(char *key);

#endif
