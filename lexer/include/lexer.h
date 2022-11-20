/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/20 03:58:52 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <stdbool.h>

enum e_token
{
	NOT_TOKEN,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
};

enum e_built_in
{
	NOT_BUILT_IN,
	ECH,
	CD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

typedef struct s_cmd
{
	char            **tab;
	int             fd_in;
	int             fd_out;
	int				token;
	int				built_in;
	struct s_cmd   *list_cmd;
	struct s_cmd   *next;
}               t_cmd;

typedef struct s_data
{
	char            **env;
	char            *input;
	int             curr_token;
	int             curr_fd_in;
	int             curr_fd_out;
	char			*hd_path;
	int             error;
	struct s_cmd   *list_cmd;
}               t_data;

/*libft*/
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int	    ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_charjoin(char *s1, char c);
int	    ft_isalnum(int c);
int	    ft_isspace(int c);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_strncmp(char *s1, char *s2, size_t n);
char    *ft_strnstr(const char *s1, const char *to_find, size_t n);
char    *ft_cpy(char *src, int skip);
char	*ft_strncpy_from(char *str, int pos, int len);
t_cmd	*ft_get_list_last(t_cmd *list);
void	ft_list_add_back(t_cmd **list, t_cmd *new);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(char *s);


/*lexer*/
void    update_quote(bool *quote);
int     check_quote_error(char *str);
int     check_quote_pos(char *str, int pos);
int	    check_token(char *str, int *i);
int	    get_var_len(char *str, int i);
char	*get_var_name(char *str, int pos, int len);
char    *get_var_val(char *var_name, int var_len, char **env);
char    *dollar_handler(char *str, int *i, char **env);

/*parser*/
int		check_built_in(char *str);
int     add_cmd(t_data *data, char *str);
char 	*create_buffer(t_data *data);
int		get_arg_len(char *str, int i);
int		redir_handler(t_data *data, char *str, int *i);
void    parse_input(t_data *data);

/*here_doc*/
char	*convert_hd_input(t_data *data, char *input);
void	get_hd_input(t_data *data, char *end);
 int	heredoc(t_data *data, char *end);

#endif