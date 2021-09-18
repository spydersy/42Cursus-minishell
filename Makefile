# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 08:04:18 by abelarif          #+#    #+#              #
#    Updated: 2021/09/18 16:45:33 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell

MINISHELL_SRCS=			./main.c\
						./minishell.c\

LIBFT_SRCS=				./libft/ft_split.c\
						./libft/ft_strlen.c\
						./libft/ft_strdup.c\
						./libft/ft_strchr.c\
						./libft/ft_substr.c\
						./libft/ft_strjoin.c\
						./libft/ft_strlcpy.c\
						./libft/ft_strncmp.c\
						./libft/ft_putstr_fd.c\
						./libft/ft_putnbr_fd.c\
						./libft/ft_putchar_fd.c\
						./libft/ft_putendl_fd.c\
						./libft/ft_strcmp.c\
						./libft/ft_atoi.c\

BUILTINS_SRCS=			./builtins/set_env.c\
						./builtins/buil_cd.c\
						./builtins/buil_pwd.c\
						./builtins/buil_env.c\
						./builtins/buil_exit.c\
						./builtins/buil_echo.c\
						./builtins/buil_unset.c\

EXECUTION_SRCS=			./execution/exec_path.c\
						./execution/execution.c\
						./execution/heredocs.c\
						./execution/execute_line.c\
						./execution/simple_builtin.c\

LINE_READER_SRCS=		./line_reader/import_line.c\
						./line_reader/get_next_line.c\


PARSING_SRCS=			./parsing/extraction.c\
						./parsing/replace_dollar.c\
						./parsing/extract_tokens.c\
						./parsing/tokens_handling.c\
						./parsing/expand_quotes.c\

UTILS_SRCS=				./utils/max_of.c\
						./utils/ft_errors.c\
						./utils/tokens_utils.c\
						./utils/env_handling.c\
						./utils/splitByIndex.c\
						./utils/grammar_checker.c\
						./utils/backslash_handling.c\
						./utils/line_handler_utils.c\

SRCS=					$(LIBFT_SRCS)\
						$(UTILS_SRCS)\
						$(PARSING_SRCS)\
						$(EXECUTION_SRCS)\
						$(MINISHELL_SRCS)\
						$(LINE_READER_SRCS)\
						$(BUILTINS_SRCS)\

OBJS=					$(SRCS:.c=.o)

# FLAGS=					-Wall -Werror -Wextra

FLAGS=					-Wall -Werror -Wextra -lreadline\
					   #	-L ~/goinfre/.brew/opt/readline/lib \
						-I ~/goinfre/.brew/opt/readline/include

$(NAME): $(OBJS)
		gcc -g3 $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

fsanitize: fclean $(OBJS)
		gcc $(FLAGS) -g3 -fsanitize=address $(SRCS) -o $(NAME)
