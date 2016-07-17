# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/05 11:15:04 by rmicolon          #+#    #+#              #
#    Updated: 2016/05/31 18:22:58 by rmicolon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wall \
		-Wextra \
		-Werror \

NAME = libft.a

SDIR = sources

SDIRPF = sources/ft_printf

ODIR = objects

SRCS = $(SDIR)/ft_memset.c \
	   $(SDIR)/ft_bzero.c \
	   $(SDIR)/ft_memcpy.c \
	   $(SDIR)/ft_memccpy.c \
	   $(SDIR)/ft_memmove.c \
	   $(SDIR)/ft_memchr.c \
	   $(SDIR)/ft_memcmp.c \
	   $(SDIR)/ft_strlen.c \
	   $(SDIR)/ft_strdup.c \
	   $(SDIR)/ft_strcpy.c \
	   $(SDIR)/ft_strncpy.c \
	   $(SDIR)/ft_strcat.c \
	   $(SDIR)/ft_strncat.c \
	   $(SDIR)/ft_strlcat.c \
	   $(SDIR)/ft_strchr.c \
	   $(SDIR)/ft_strrchr.c \
	   $(SDIR)/ft_strstr.c \
	   $(SDIR)/ft_strnstr.c \
	   $(SDIR)/ft_strcmp.c \
	   $(SDIR)/ft_strncmp.c \
	   $(SDIR)/ft_atoi.c \
	   $(SDIR)/ft_isalpha.c \
	   $(SDIR)/ft_isdigit.c \
	   $(SDIR)/ft_isalnum.c \
	   $(SDIR)/ft_isascii.c \
	   $(SDIR)/ft_isprint.c \
	   $(SDIR)/ft_toupper.c \
	   $(SDIR)/ft_tolower.c \
	   $(SDIR)/ft_memalloc.c \
	   $(SDIR)/ft_memdel.c \
	   $(SDIR)/ft_strnew.c \
	   $(SDIR)/ft_strdel.c \
	   $(SDIR)/ft_strclr.c \
	   $(SDIR)/ft_striter.c \
	   $(SDIR)/ft_striteri.c \
	   $(SDIR)/ft_strmap.c \
	   $(SDIR)/ft_strmapi.c \
	   $(SDIR)/ft_strequ.c \
	   $(SDIR)/ft_strnequ.c \
	   $(SDIR)/ft_strsub.c \
	   $(SDIR)/ft_strjoin.c \
	   $(SDIR)/ft_strtrim.c \
	   $(SDIR)/ft_strsplit.c \
	   $(SDIR)/ft_itoa.c \
	   $(SDIR)/ft_putchar.c \
	   $(SDIR)/ft_putstr.c \
	   $(SDIR)/ft_putendl.c \
	   $(SDIR)/ft_putnbr.c \
	   $(SDIR)/ft_putchar_fd.c \
	   $(SDIR)/ft_putstr_fd.c \
	   $(SDIR)/ft_putendl_fd.c \
	   $(SDIR)/ft_putnbr_fd.c \
	   $(SDIR)/ft_lstnew.c \
	   $(SDIR)/ft_lstdelone.c \
	   $(SDIR)/ft_lstdel.c \
	   $(SDIR)/ft_lstadd.c \
	   $(SDIR)/ft_lstiter.c \
	   $(SDIR)/ft_lstmap.c \
	   $(SDIR)/ft_strndup.c \
	   $(SDIR)/ft_strtrimc.c \
	   $(SDIR)/ft_isblank.c \
	   $(SDIR)/ft_isupper.c \
	   $(SDIR)/ft_islower.c \
	   $(SDIR)/ft_abs.c \
	   $(SDIR)/ft_strrev.c \
	   $(SDIR)/get_next_nbr.c \
	   $(SDIR)/get_next_line.c \
	   $(SDIR)/ft_itoa_base.c \
	   $(SDIR)/print_memory.c \

PFSRCS = $(SDIRPF)/ft_printf.c \
		 $(SDIRPF)/ftprf_init.c \
		 $(SDIRPF)/ftprf_parse_flags.c \
		 $(SDIRPF)/ftprf_bonus_conv.c \
		 $(SDIRPF)/ftprf_alpha_conv.c \
		 $(SDIRPF)/ftprf_xof_conv.c \
		 $(SDIRPF)/ftprf_diu_conv.c \
		 $(SDIRPF)/ftprf_xtox.c \
		 $(SDIRPF)/ftprf_pre_digitflags.c \
		 $(SDIRPF)/ftprf_pre_alphaflags.c \
		 $(SDIRPF)/ftprf_postflags.c \
		 $(SDIRPF)/ftprf_print_width.c \
		 $(SDIRPF)/ftprf_print_digit.c \
		 $(SDIRPF)/ftprf_print_alpha.c \
		 $(SDIRPF)/ftprf_print_lc.c \
		 $(SDIRPF)/ftprf_tools.c \


OBJ = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)

PFOBJ = $(PFSRCS:$(SDIRPF)/%.c=$(ODIR)/%.o)

HDRS =  -I./includes/

all: $(NAME)

$(NAME): $(ODIR) $(OBJ) $(PFOBJ)
	@ar rc $@ $(OBJ) $(PFOBJ)
	@echo "Lib created."

$(ODIR):
	@echo "Wait... \c"
	@mkdir $@

$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(FLAGS) -c $< $(HDRS) -o $@

$(ODIR)/%.o: $(SDIRPF)/%.c
	@$(CC) $(FLAGS) -c $< $(HDRS) -o $@

clean:
	@rm -rf $(ODIR)
	@echo "Lib-objects deleted."

fclean: clean
	@rm -rf $(NAME)
	@echo "Lib deleted."

re: fclean all

.PHONY: all clean fclean re
