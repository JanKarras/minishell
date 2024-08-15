/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:52:39 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/01 14:55:54 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_only(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '=' && key[i])
		i++;
	return (ft_substr(key, 0, i));
}

char	*value_only(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '=' && key[i])
		i++;
	if (!key[i])
		return (NULL);
	return (&key[i + 1]);
}

char	*create_keypair(char *name, char *value)
{
	char	*key;
	int		key_size;
	int		i;

	key_size = ft_strlen(name) + ft_strlen(value) + 2;
	key = malloc(key_size * sizeof(char));
	i = 0;
	while (*name)
		key[i++] = *name++;
	key[i++] = '=';
	while (*value)
		key[i++] = *value++;
	key[i] = '\0';
	return (key);
}
