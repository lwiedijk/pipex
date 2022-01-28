# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/27 11:19:54 by lwiedijk      #+#    #+#                  #
#    Updated: 2022/01/28 14:08:57 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex
HEADERS = pipex.h
SRCS =	main.c \
		pipex.c parser.c utils.c \
		error.c free.c \

OBJS_DIR = objs/
_OBJS = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(_OBJS))

LIBFT_DIR = libft/
LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT) ./
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L. -lft -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	rm -f outfile
	./pipex infile.txt "cat -e" "cat -e" "/bin/cat -e" outfile
	< infile.txt cat -e | cat -e | /bin/cat -e  > outfile_term

test_leaks: all
	rm -f outfile
	valgrind ./pipex infile.txt "cat -e" "wc" outfile

clean:
	rm -f $(LIBFT) $(_OBJS) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
