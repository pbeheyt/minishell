/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:21:09 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/26 06:45:27 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_env *mini)
{
	t_env	*tmp;

	tmp = mini;
	while (tmp)
	{
		if (ft_strchr(tmp->line, '='))
			printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}

void	ft_remove_list(t_env *old, t_env *tmp)
{
	if (tmp && old)
	{
		free(tmp->line);
		if (tmp->next)
			old->next = tmp->next;
		else
			old->next = NULL;
		free(tmp);
		return ;
	}
	else
	{
		if (tmp->next)
		{
			free(tmp->line);
			tmp->line = ft_strdup(tmp->next->line);
			ft_remove_list(tmp, tmp->next);
		}
		else
		{
			free(tmp->line);
			tmp->line = NULL;
		}
	}
}

void	ft_remove_if_in_env(t_env *mini, char *args)
{
	t_env	*tmp;
	t_env	*old;
	char	*tmp_args;

	tmp = mini;
	old = NULL;
	while (tmp)
	{
		tmp_args = ft_cpy_env_name(args);
		if (ft_strncmp(tmp->line, tmp_args, ft_strlen(tmp_args)) == 0)
		{
			ft_remove_list(old, tmp);
			free(tmp_args);
			return ;
		}
		free(tmp_args);
		old = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset_builtin(t_cmd *cmd, t_env *mini)
{
	int	i;
	int	error;

	if (!cmd->tab[1] || !mini || !mini->line)
	{
		write(2, "unset : error initialisation\n", 29);
		return (g_exit = 1, 1);
	}
	i = 1;
	while (cmd->tab && cmd->tab[i])
	{
		g_exit = 0;
		error = ft_is_valid_env(cmd->tab[i]);
		if (error < 0)
		{
			g_exit = 1;
			write(2, cmd->tab[i], ft_strlen(cmd->tab[i]));
			write(2, " : unset : invalid parameter name\n", 34);
		}
		else
			ft_remove_if_in_env(mini, cmd->tab[i]);
		i++;
	}
	return (g_exit);
}
