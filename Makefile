# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/27 11:19:54 by lwiedijk      #+#    #+#                  #
#    Updated: 2022/02/10 13:43:23 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =			pipex

SRCS_DIR =		srcs/
OBJS_DIR =		objs/
HEADERS_DIR =	includes/
SRCS =			pipex.c child_process.c parser.c \
				error.c free.c utils.c
NORMAL =		main.c
BONUS = 		main_bonus.c here_doc.c
HEADERS =		pipex.h
_OBJS =			$(SRCS:.c=.o)
_NORMAL =		$(NORMAL:.c=.o)
_BONUS =		$(BONUS:.c=.o)

ifdef WITH_PIPEX_BONUS
	OBJS =		$(addprefix $(OBJS_DIR), $(_OBJS) $(_BONUS))
	OTHER =		$(addprefix $(OBJS_DIR), $(_NORMAL))
else
	OBJS =		$(addprefix $(OBJS_DIR), $(_OBJS) $(_NORMAL))
	OTHER =		$(addprefix $(OBJS_DIR), $(_BONUS))
endif

LIBFT_DIR =	libft/

CFLAGS =	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	rm -f $(OTHER)
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -Llibft/ -lft -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS_DIR)$(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -Ilibft/ -c $< -o $@

bonus:
	$(MAKE) WITH_PIPEX_BONUS=1 all

clean:
	rm -f $(OBJS) $(OTHER)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
