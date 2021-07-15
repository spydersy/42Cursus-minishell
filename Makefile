# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 08:04:18 by abelarif          #+#    #+#              #
#    Updated: 2021/07/15 10:50:23 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell

MINISHELL_SRCS=	./main.c\
				./minishell.c\

LIBFT_SRCS=		./libft/ft_atoi.c\
				./libft/ft_memmove.c\
				./libft/ft_strlcpy.c\
				./libft/ft_bzero.c \
				./libft/ft_memset.c\
				./libft/ft_strlen.c\
				./libft/ft_calloc.c\
				./libft/ft_putchar_fd.c\
				./libft/ft_strmapi.c\
				./libft/ft_isalnum.c\
				./libft/ft_putendl_fd.c\
				./libft/ft_strncmp.c\
				./libft/ft_isalpha.c\
				./libft/ft_putnbr_fd.c\
				./libft/ft_strnstr.c\
				./libft/ft_isascii.c\
				./libft/ft_putstr_fd.c\
				./libft/ft_strrchr.c\
				./libft/ft_isdigit.c\
				./libft/ft_split.c\
				./libft/ft_strtrim.c\
				./libft/ft_isprint.c\
				./libft/ft_memccpy.c\
				./libft/ft_strchr.c\
				./libft/ft_substr.c\
				./libft/ft_itoa.c\
				./libft/ft_memchr.c\
				./libft/ft_strdup.c\
				./libft/ft_tolower.c\
				./libft/ft_memcmp.c\
				./libft/ft_strjoin.c\
				./libft/ft_toupper.c\
				./libft/ft_memcpy.c\
	           	./libft/ft_strlcat.c\

EXECUTION_SRCS=	./execution/to_execution.c\

LINE_READER_SRCS=		./line_reader/get_next_line.c\
						./line_reader/import_line.c\

PARSING_SRCS=			./parsing/extraction.c\
						./parsing/extract_tokens.c\
						./parsing/replace_dollar.c\
						./parsing/tokens_handling.c\

UTILS_SRCS=				./utils/backslash_handling.c\
						./utils/ft_errors.c\
						./utils/max_of.c\
						./utils/tokens_utils.c\
						./utils/env_handling.c\
						./utils/line_handler_utils.c\
						./utils/splitByIndex.c\

SRCS=			$(MINISHELL_SRCS)\
				$(LIBFT_SRCS)\
				$(EXECUTION_SRCS)\
				$(LINE_READER_SRCS)\
				$(PARSING_SRCS)\
				$(UTILS_SRCS)\

OBJS=			$(SRCS:.c=.o)

FLAGS=			-Wall -Werror -Wextra

$(NAME): $(OBJS)
		clang-9 -g3 $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

fsanitize: fclean $(OBJS)
		clang-9 $(FLAGS) -g3 -fsanitize=address $(SRCS) -o $(NAME)
