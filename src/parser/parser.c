/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/12 16:48:18 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmd(t_data *data)
{
	data->buf = create_buffer();
	if (!data->buf)
		return (free_all_exit(data, 1), 1);
	data->fd_in = 0;
	data->fd_out = 1;
	data->file_error = 0;
	return (0);
}

int	add_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free_all_exit(data, 1), 1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split_parser(data->buf);
	if (!cmd->tab)
		return (free_all_exit(data, 1), 1);
	if (!cmd->tab[0])
		return (free_tab(cmd->tab), free(cmd), 1);
	cmd->fd_in = data->fd_in;
	cmd->fd_out = data->fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

int	parse_input(t_data *data)
{
	int		i;

	init_cmd(data);
	data->nb_hd = 0;
	i = -1;
	while (data->input[++i])
	{
		data->token = get_token_code(data->input, &i);
		if (data->token == PIPE)
		{
			if (!data->file_error)
				add_cmd(data);
			free(data->buf);
			init_cmd(data);
		}
		else if (data->token && !data->file_error)
			redir_handler(data, data->input, &i);
		else if (data->token == NOT_TOKEN)
			data->buf = convert_input(data, data->buf, data->input, &i);
	}
	if (!data->file_error)
		add_cmd(data);
	free(data->buf);
	return (0);
}
