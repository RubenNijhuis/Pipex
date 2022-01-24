# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rnijhuis <rnijhuis@studentcodam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 10:35:30 by rnijhuis      #+#    #+#                  #
#    Updated: 2022/01/24 14:54:17 by rnijhuis      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := pipex
INCLUDE_DIR := includes
SRC_DIR := src
BIN_DIR := ./bin

SRCS := src/main.c \
		src/get_path_to_binary.c

INCLUDES := $(INCLUDE_DIR)libft.a\

CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS)

$(NAME):$(OBJS) ./includes/pipex.h
	$(COMPILE) $(SRCS) -L ./includes/ -lft -o $(NAME)

libft:
	make -C ./LibFT/src
	mv ./LibFT/src/libft.a $(INCLUDE_DIR)
	cp ./LibFT/src/libft.h $(INCLUDE_DIR)
	echo "📦 Moving libft to $(INCLUDE_DIR)"

run:
	./$(NAME) assets/text1.txt "ls -l" "ls -l" assets/text2.txt

all: libft $(NAME)

clean:
	rm -rf $(OBJS)
	echo "🧹 Removing object files"

fclean: clean
	rm -rf ./bin/$(NAME)
	echo "🧹 Removing $(NAME) executable"

re: fclean all

.PHONY: run all clean fclean re libft