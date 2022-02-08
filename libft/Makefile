# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/30 16:06:46 by lwiedijk      #+#    #+#                  #
#    Updated: 2022/02/08 08:55:10 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NAME = 			libft.a
HEADERS = 		libft.h
SRCS = 			ft_atoi.c			\
				ft_atol.c			\
	  			ft_bzero.c			\
	  			ft_calloc.c			\
	  			ft_isalnum.c		\
	  			ft_isalpha.c		\
	  			ft_isascii.c		\
	  			ft_isdigit.c		\
				ft_isdigit_min.c	\
	  			ft_isprint.c		\
				ft_iswhitespace.c	\
				ft_itoa_base_unsigned.c	\
				ft_itoa_base.c		\
	  			ft_itoa.c			\
	  			ft_memccpy.c		\
	  			ft_memchr.c			\
	  			ft_memcmp.c			\
	  			ft_memcpy.c			\
	  			ft_memmove.c		\
	  			ft_memset.c			\
	  			ft_putchar_fd.c		\
	  			ft_putendl_fd.c		\
	  			ft_putnbr_fd.c		\
	  			ft_putstr_fd.c		\
	  			ft_split.c			\
				ft_split_and_count.c \
	  			ft_strchr.c			\
	  			ft_strdup.c			\
	  			ft_strjoin.c		\
				ft_strjoin_free.c	\
	  			ft_strlcat.c		\
	  			ft_strlcpy.c		\
	  			ft_strlen.c			\
	  			ft_strmapi.c		\
	  			ft_strncmp.c		\
	  			ft_strnstr.c		\
	  			ft_strrchr.c		\
	  			ft_strtrim.c		\
	  			ft_substr.c			\
				ft_tolower.c		\
				ft_toupper.c		\
				ft_numlen_base.c	\
				ft_power.c			\
				ft_putchar.c		\
				ft_putnbr.c			\
				ft_putstr.c			\
				ft_strcat.c			\
				ft_strjoin_free.c	\
				ft_strcmp.c			\
				ft_strcpy.c			\
				get_next_line.c		\

BONUS_FILES	=	ft_lstadd_front.c	\
				ft_lstadd_back.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstlast.c		\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_lstsize.c		\

OBJS_DIR = objs/
_OBJS = $(SRCS:.c=.o)
_BONUS_OBJS = $(BONUS_FILES:.c=.o)

ifdef WITH_BONUS
OBJS = $(addprefix $(OBJS_DIR), $(_OBJS) $(_BONUS_OBJS))
else
OBJS = $(addprefix $(OBJS_DIR), $(_OBJS))
endif

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(addprefix $(OBJS_DIR), $(_OBJS) $(_BONUS_OBJS))

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
