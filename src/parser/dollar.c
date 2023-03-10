/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/10 23:57:34 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_env_name(t_data *data, char *str, int *i)
{
	char	*var;
	char	*tmp;
	int		j;

	var = create_buffer();
	if (!var)
		return (free_all_exit(data, 1), NULL);
	j = *i - 1;
	if (ft_isdigit(str[*i]))
	{
		while (ft_isdigit(str[++j]))
		{
			tmp = ft_charjoin(var, str[j]);
			free(var);
			var = tmp;
		}
		return (var);
	}
	while (ft_isalnum(str[++j]) || str[j] == '_')
	{
		tmp = ft_charjoin(var, str[j]);
		free(var);
		var = tmp;
	}
	return (var);
}

char	*get_var_env_val(char *var_env, int len, t_env *mini)
{
	t_env	*tmp;

	tmp = mini;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, var_env, len) && tmp->line[len] == '=')
			return (ft_cpy(tmp->line, len + 1));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_dollar(t_data *data, char *str, int *i, t_env *mini)
{
	char	*var_env_name;
	char	*dollar;

	*i += 1;
	if (str[*i] == '?')
	{
		dollar = ft_itoa(g_exit);
		*i += ft_strlen(dollar) - 1;
	}
	else
	{	
		var_env_name = get_var_env_name(data, str, i);
		if (!var_env_name)
			return (NULL);
		*i += ft_strlen(var_env_name) - 1;
		if (!var_env_name[0])
			return (free(var_env_name), NULL);
		dollar = get_var_env_val(var_env_name, ft_strlen(var_env_name), mini);
		if (!dollar)
			return (free(var_env_name), NULL);
		free(var_env_name);
	}
	return (dollar);
}
