# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 09:25:10 by ael-ghem          #+#    #+#              #
#    Updated: 2021/07/01 07:46:32 by ael-ghem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************************** NAME *************************************
NAME = pipex
BONUS = pipex_bonus
# *****************************************************************************

# ********************************** SRCS *************************************
SRCS_DIR = ./
SRCS =	pipex.c	tools.c	here_doc.c
SRCS_BONUS =	pipex_bonus.c	tools.c	here_doc.c
INCS = 	pipex.h
# *****************************************************************************

# ********************************** FLAGS ************************************
FLAGS = -g3  -Wall -Wextra -Werror
# *****************************************************************************

# ********************************** OBJS *************************************
OBJS_DIR 	= 	objs/
OBJ 		= 	$(SRCS:.c=.o)
OBJ_BONUS	=	$(SRCS_BONUS:.c=.o)
OBJS_BONUS	= 	$(addprefix $(OBJS_DIR), $(OBJ_BONUS))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(OBJ))
# *****************************************************************************

# ****************************** SUBJECT RELATED ******************************

$(OBJS_DIR)%.o	:	$(SRCS_DIR)%.c $(INCS)
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling : $<"
	@clang $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@clang $(FLAGS) -o $(NAME) $(OBJS)

$(BONUS) : $(OBJS_BONUS)
	@clang $(FLAGS) -o $(BONUS) $(OBJS_BONUS)

all: $(NAME)

bonus: $(BONUS)

clean:
	@echo "Cleaning: $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Cleaning: $(NAME) and $(BONUS)"
	@rm -f $(NAME) $(BONUS)

re: fclean all
# *****************************************************************************