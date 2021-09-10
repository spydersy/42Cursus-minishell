# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 08:04:18 by abelarif          #+#    #+#              #
#    Updated: 2021/09/10 11:58:23 by abelarif         ###   ########.fr        #
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

# BUILTINS_SRCS=			./builtins/buil_export.c\
						

EXECUTION_SRCS=			./execution/to_execution.c\
						./execution/to_execution2.c\

LINE_READER_SRCS=		./line_reader/import_line.c\
						./line_reader/get_next_line.c\


PARSING_SRCS=			./parsing/extraction.c\
						./parsing/replace_dollar.c\
						./parsing/extract_tokens.c\
						./parsing/tokens_handling.c\

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

OBJS=					$(SRCS:.c=.o)

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
