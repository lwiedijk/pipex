# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/27 11:19:54 by lwiedijk      #+#    #+#                  #
#    Updated: 2022/02/04 09:05:23 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		pipex
HEADERS =	pipex.h get_next_line.h
SRCS =		pipex.c parser.c utils.c \
			error.c free.c
NORMAL =	main.c child_process.c
BONUS = 	main_bonus.c child_process_bonus.c \
			here_doc.c get_next_line.c get_next_line_utils.c


OBJS_DIR =	objs/
_OBJS =		$(SRCS:.c=.o)
_NORMAL =	$(NORMAL:.c=.o)
_BONUS =	$(BONUS:.c=.o)

ifdef WITH_PIPEX_BONUS
	OBJS =		$(addprefix $(OBJS_DIR), $(_OBJS) $(_BONUS))
	OTHER =		$(addprefix $(OBJS_DIR), $(_NORMAL))
else
	OBJS =		$(addprefix $(OBJS_DIR), $(_OBJS) $(_NORMAL))
	OTHER =		$(addprefix $(OBJS_DIR), $(_BONUS))
endif

LIBFT_DIR =	libft/
LIBFT =		libft.a

CFLAGS =	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	rm -f $(OTHER)
	make bonus -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT) ./
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L. -lft -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	$(MAKE) WITH_PIPEX_BONUS=1 all

clean:
	rm -f $(LIBFT) $(_OBJS) $(OBJS) $(OTHER)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
