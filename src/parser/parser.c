/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/25 05:09:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_cmd(t_data *data, char *buffer)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split(buffer);
	cmd->fd_in = data->curr_fd_in;
	cmd->fd_out = data->curr_fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

char	*create_buffer(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	return (buffer);
}

int	check_token(t_data *data, char *buf, int *i)
{
	data->curr_token = get_token_code(data->input, i);
	if (data->curr_token > PIPE)
		redir_handler(data, data->input, i);
	if (data->curr_token == PIPE)
	{
		add_cmd(data, buf);
		free(buf);
		return (1);
	}
	return (0);
}
char	*convert_input(t_data *data, char *input, char *buf, int *i)
{
	char	*tmp;
	char	*env;

	if (input[*i] == '$' && check_quote_pos(input, *i) != 1)
	{	
		env = dollar_handler(input, i, data->env);
		tmp = ft_strjoin(buf, env);
		free(buf);
		free(env);
		buf = tmp;
	}
	else
	{	
		tmp = ft_charjoin(buf, data->input[*i]);
		free(buf);
		buf = tmp;
	}
	return (buf);
}

int	parse_input(t_data *data)
{
	int		i;
	char	*buf;

	if (check_quote_error(data->input))
		return (printf("quote error\n"), 1);
	buf = create_buffer();
	if (!buf)
		return (1);
	i = -1;
	while (data->input[++i])
	{
		if (check_token(data, buf, &i))
		{
			buf = create_buffer();
			if (!buf)
				return (1);
		}
		buf = convert_input(data, data->input, buf, &i);
	}
	add_cmd(data, buf);
	free(buf);
	return (0);
}

// int	parse_input(t_data *data)
// {
// 	int		i;
// 	char	*buf;
// 	char	*tmp;
// 	char	*env;

// 	if (check_quote_error(data->input))
// 		return (printf("quote error\n"), 1);
// 	buf = create_buffer();
// 	if (!buf)
// 		return (1);
// 	i = -1;
// 	while (data->input[++i])
// 	{
// 		data->curr_token = check_token(data->input, &i);
// 		if (data->curr_token == PIPE)
// 		{
// 			add_cmd(data, buf);
// 			free(buf);
// 			buf = create_buffer();
// 			if (!buf)
// 				return (1);
// 		}
// 		else if (data->curr_token > PIPE)
// 			redir_handler(data, data->input, &i);
// 		else if (data->input[i] == '$' && check_quote_pos(data->input, i) != 1)
// 		{	
// 			env = dollar_handler(data->input, &i, data->env);
// 			tmp = ft_strjoin(buf, env);
// 			free(buf);
// 			free(env);
// 			buf = tmp;
// 		}
// 		else
// 		{	
// 			tmp = ft_charjoin(buf, data->input[i]);
// 			free(buf);
// 			buf = tmp;
// 		}
// 	}
// 	add_cmd(data, buf);
// 	free(buf);
// 	return (0);
// }