# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/07 12:52:37 by jwalle            #+#    #+#              #
#    Updated: 2016/07/07 12:59:15 by jwalle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Corewar

ALL_CFLAGS	= -Wall -Wextra -Werror 
CC			= clang
RM			= rm -rf

LIBFT_DIR	= ./libft
INC			=	-I./includes -I./libft/includes
LINK		=	-L./libft -lft -lncurses 
OBJS_DIR	= objs
SRCS_DIR	= srcs
INCS_DIR	= includes

SRCS		= main.c			\
			  
OBJS		= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))


all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) -o $(NAME) $(OBJS) $(LINK)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(ALL_CFLAGS) $(INC) -c $< -o $@
	@echo "\033[A\033[K\033[A"

clean:
	make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

.PHONY: all clean fclean re
