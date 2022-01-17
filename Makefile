# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rnijhuis <rnijhuis@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 10:35:30 by rnijhuis      #+#    #+#                  #
#    Updated: 2022/01/17 10:05:59 by rnijhuis      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := pipex
INCLUDE_DIR := include
SRC_DIR := src
BIN_DIR := ./bin/

SRCS := src/main.c

INCLUDES := ./include/libft.a\

CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS)

TES_DATA = test1.txt cat cat test2.txt

$(NAME): $(OBJS) ./include/$(NAME).h
	@$(COMPILE) $(SRCS) $(INCLUDES) -I $(INCLUDE_DIR) -o $(BIN_DIR)$(NAME)

libft:
	@make -C ./LibFT/src
	@mv ./LibFT/src/libft.a ./include
	@cp ./LibFT/src/libft.h ./include
	@echo "📦 Moving libft to 'include'"

run:
	./bin/$(NAME) $(TEST_DATA)

all: libft run

clean:
	@rm -rf $(OBJS)
	@echo "🧹 Removing object files"

fclean: clean
	@rm -rf ./bin/$(NAME)
	@echo "🧹 Removing $(NAME) executable"

re: fclean all

.PHONY: run all clean fclean re libft