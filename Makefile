# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 08:04:18 by abelarif          #+#    #+#              #
#    Updated: 2021/07/15 08:22:32 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell

MINISHELL_SRCS=	./main.c\
				./minishell.c\

# LIBFT_SRCS=		./libft/*.c\

LIBFT_SRCS=		./libft/ft_atoi.c\
				./libft/ft_memmove.c\
				./libft/ft_strlcpy.c\
				./libft/ft_bzero.c \
				./libft/ft_memset.c\
				./libft/ft_strlen.c\
				./libft/ft_calloc.c\
				./libft/ft_putchar_fd.c\
				./libft/ft_strmapi.c\
				./libft/ft_isalnum.c  \
				./libft/ft_putendl_fd.c\
				./libft/ft_strncmp.c\
				./libft/ft_isalpha.c   \
				./libft/ft_putnbr_fd.c\
				./libft/ft_strnstr.c\
				./libft/ft_isascii.c   \
				./libft/ft_putstr_fd.c\
				./libft/ft_strrchr.c\
				./libft/ft_isdigit.c   \
				./libft/ft_split.c\
				./libft/ft_strtrim.c\
				./libft/ft_isprint.c   \
				./libft/ft_memccpy.c        \
				./libft/ft_strchr.c\
				./libft/ft_substr.c\
				./libft/ft_itoa.c      \
				./libft/ft_memchr.c        \
				./libft/ft_strdup.c\
				./libft/ft_tolower.c\
				./libft/ft_memcmp.c           \
				./libft/ft_strjoin.c\
				./libft/ft_toupper.c\
				./libft/ft_memcpy.c\
	           	./libft/ft_strlcat.c\

EXECUTION_SRCS=	./execution/start_execution.c\

GNL_SRCS=		./gnl/get_next_line.c\

PARSING_SRCS=	./parsing/backslash_handling.c\
				./parsing/ft_errors.c\
				./parsing/replace_dollar.c\
				./parsing/env_handling.c\
				./parsing/import_line.c\
				./parsing/tokens_handling.c\
				./parsing/extraction.c\
				./parsing/index_split.c\
				./parsing/extract_tokens2.c\
				./parsing/line_handling_utils.c\

SRCS=			$(MINISHELL_SRCS)\
				$(LIBFT_SRCS)\
				$(EXECUTION_SRCS)\
				$(GNL_SRCS)\
				$(PARSING_SRCS)\

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