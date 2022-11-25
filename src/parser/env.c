/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/24 02:46:18 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_name(char *str, int *i)
{
	char	*var;
	char	*tmp;

	var = create_buffer();
	if (!var)
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		tmp = ft_charjoin(var, str[*i]);
		free(var);
		var = tmp;
		*i += 1;
	}
	*i -= 1;
	return (var);
}

char	*get_var_val(char *var_name, int var_len, char **env)
{
	int	l;

	l = -1;
	while (env[++l])
	{
		if (ft_strnstr(env[l], var_name, var_len))
			return (ft_cpy(env[l], var_len + 1));
	}
	return (NULL);
}

char	*dollar_handler(char *str, int *i, char **env)
{
	char	*var_name;
	char	*var_val;

	*i += 1;
	if (!str[*i])
		return (NULL);
	// else if (!str[*i] == '?')
		//...Stores the exit value of the last command that was executed
	else
	{	
		var_name = get_var_name (str, i);
		if (!var_name)
			return (NULL);
		var_val = get_var_val(var_name, ft_strlen(var_name), env);
		free(var_name);
	}	
	return (var_val);
}