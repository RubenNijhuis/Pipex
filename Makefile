# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rnijhuis <rnijhuis@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 10:35:30 by rnijhuis      #+#    #+#                  #
#    Updated: 2022/01/20 16:27:07 by rnijhuis      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := pipex
INCLUDE_DIR := includes
SRC_DIR := src
BIN_DIR := ./bin/

SRCS := src/main.c

INCLUDES := ./includes/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS)

TES_DATA = test1.txt cat cat test2.txt

$(NAME): $(OBJS) ./includes/pipex.h
	@$(COMPILE) $(SRCS) $(INCLUDES) -I $(INCLUDE_DIR) -o $(BIN_DIR)$(NAME)

libft:
	@make -C ./LibFT/src
	@mv ./LibFT/src/libft.a ./includes/
	@cp ./LibFT/src/libft.h ./includes/
	@echo "📦 Moving libft to 'include'"

run:
	./bin/$(NAME) assets/text1.txt "ls -l" "wc -l" assets/text2.txt

all: libft run

clean:
	@rm -rf $(OBJS)
	@echo "🧹 Removing object files"

fclean: clean
	@rm -rf ./bin/$(NAME)
	@echo "🧹 Removing $(NAME) executable"

re: fclean all

.PHONY: run all clean fclean re libft