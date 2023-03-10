/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/12 01:16:49 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote_error(char *str)
{
	bool	simple_quote;
	bool	double_quote;
	int		i;

	if (!str)
		return (-1);
	simple_quote = false;
	double_quote = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && double_quote == false)
			update_quote(&simple_quote);
		if (str[i] == '\"' && simple_quote == false)
			update_quote(&double_quote);
	}
	if (double_quote == true)
		return (2);
	if (simple_quote == true)
		return (1);
	return (0);
}

int	check_around_token(char *str, int pos, int token)
{
	int	i;
	int	next_token;

	if (token == PIPE)
	{
		i = pos - 1;
		while (ft_isspace(str[i]))
			i--;
		if (!i)
			return (PIPE);
	}
	i = pos;
	while (ft_isspace(str[i]))
			i++;
	if (token == PIPE && str[i] == '|')
		return (PIPE);
	next_token = get_token_code(str, &i);
	if (token != PIPE && next_token)
		return (next_token);
	if (!str[i])
		return ('\n');
	return (0);
}

int	check_token_error(char *str)
{
	int	i;
	int	token;
	int	error;

	i = -1;
	while (str[++i])
	{
		token = get_token_code(str, &i);
		if (token)
		{
			i++;
			error = check_around_token(str, i, token);
			if (error)
				return (error);
		}
	}
	return (0);
}

void	print_token(int error)
{
	if (error == 5)
	{
		write(2, "|", 1);
		return ;
	}
	while (error > 0)
	{
		if (error == 1 || error == 3)
			write(2, "<", 1);
		else if (error == 2 || error == 4)
			write(2, ">", 1);
		error -= 2;
	}
}

int	check_error(char *input)
{
	int	error;

	error = check_quote_error(input);
	if (error)
	{
		write(2, "minishell : syntax error ", 25);
		if (error == 1)
			write(2, "simple ", 7);
		else if (error == 2)
			write(2, "double ", 7);
		write(2, "quotes not closing\n", 19);
		return (g_exit = 2, 2);
	}
	error = check_token_error(input);
	if (error)
	{
		write(2, "minishell : syntax error near unexpected token `", 48);
		if (error == '\n')
			write(2, "newline", 7);
		else
			print_token(error);
		write(2, "'\n", 2);
		return (g_exit = 2, 2);
	}
	return (0);
}
