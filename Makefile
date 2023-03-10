NAME			=	minishell

FLAGS			=	-Wall -Wextra -Werror -g

DIR_SRC			=	src
DIR_OBJ			=	obj
SUB_OBJ			=	obj/parser obj/libft obj/builtins obj/exec

SRC				=	parser/clear.c parser/dollar.c parser/error.c parser/heredoc.c parser/parser_utils.c parser/parser.c parser/quote.c parser/redir.c parser/token.c \
					libft/libft_charset.c libft/libft_cleaning.c libft/libft_list_1.c libft/libft_list_2.c \
					libft/libft_str_search.c libft/libft_utils.c libft/libft_modify_str.c libft/libft_split_parser.c \
					minishell.c signal.c \
					exec/exec.c exec/utils.c exec/ft_split.c \
					builtins/export.c builtins/export_utils.c builtins/echo.c builtins/pwd.c builtins/unset.c builtins/cd.c builtins/exit.c\



OBJ				=	$(SRC:%.c=$(DIR_OBJ)/%.o)
DEP				=	$(SRC:%.c=$(DIR_OBJ)/%.d)

RED				=	$'\e[0;31m
GREEN			=	$'\e[32m
YELLOW			=	$'\e[33m
BOLD			=	$'\e[1m
UNDER			=	$'\e[4m
END				=	$'\e[0m

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c Makefile
					mkdir -p $(DIR_OBJ) $(SUB_OBJ)
					echo "Compiling - ${YELLOW}${BOLD}${UNDER}$<${END}..."
					$(CC) $(FLAGS) -MMD -c $< -o $@
					echo "${GREEN}Done !${END}"

$(NAME):			$(OBJ)
					echo "Compiling - ${YELLOW}${BOLD}${UNDER}./minishell${END}..."
					$(CC) $(OBJ) -o $(NAME) -lreadline
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

all:				$(NAME)

clean:
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

fclean:
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./minishell${END}..."
					rm -rf $(NAME)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

re:
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./minishell${END}..."
					rm -rf $(NAME)
					echo "${GREEN}Done !${END}"
					make --no-print-directory all

git:
					git add .
					git commit -m "$(NAME)"
					git push

leaks:
					valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --log-file="test1" --suppressions="rl_leaks.txt" -s ./minishell

-include $(DEP)

.PHONY:				all clean fclean re git leaks
.SILENT:
