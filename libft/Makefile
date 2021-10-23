# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smiller <smiller@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/18 12:47:42 by smiller       #+#    #+#                  #
#    Updated: 2020/11/04 08:49:54 by smiller       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
HEADER_LIBFT = libft.h
OBJ_FILES = ft_memset.o \
			ft_bzero.o \
			ft_memcpy.o \
			ft_memccpy.o \
			ft_memmove.o \
			ft_memchr.o \
			ft_memcmp.o \
			ft_strlen.o \
			ft_pathlen.o\
			ft_strlcpy.o \
			ft_strlcat.o \
			ft_strchr.o \
			ft_strrchr.o \
			ft_strnstr.o \
			ft_strncmp.o \
			ft_atoi.o \
			ft_isalpha.o \
			ft_isdigit.o \
			ft_isalnum.o \
			ft_isascii.o \
			ft_isprint.o \
			ft_toupper.o \
			ft_tolower.o \
			ft_calloc.o \
			ft_strdup.o \
			ft_substr.o \
			ft_strjoin.o \
			ft_strtrim.o \
			ft_split.o \
			ft_itoa.o \
			ft_strmapi.o \
			ft_putchar_fd.o \
			ft_putstr_fd.o \
			ft_putendl_fd.o \
			ft_putnbr_fd.o \
			get_next_line.o\

CYAN   = \x1b[36m
RESET   = \x1b[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rc $@ $^
	@ranlib $(NAME)

%.o: %.c $(HEADER_LIBFT)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
