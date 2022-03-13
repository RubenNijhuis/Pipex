# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rnijhuis <rnijhuis@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/12 11:05:57 by rnijhuis      #+#    #+#                  #
#    Updated: 2022/03/13 19:00:17 by rubennijhui   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

NAME := pipex
INCLUDE_DIR := include
SRC_DIR := src
LIBS_DIR := libs
OBJS_DIR := objs

#=====================================#
#============ Input files ============#
#=====================================#

LIBS := $(LIBS_DIR)/LibFT/libft.a \

LIBS_HEADERS := -I $(LIBS_DIR)/LibFT/include/ \

INC := -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRCS := main.c \
		processes.c \
		utils/get_path_to_binary.c \
		utils/ft_split.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g $(INC)
LDFLAGS =

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

run:
	./$(NAME) assets/text1.txt "ls -l" "wc" assets/text2.txt

$(NAME):$(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "✅ Built $(NAME)"

$(LIBS_DIR)/LibFT/libft.a:
	@make -C $(LIBS_DIR)/LibFT

submodules:
	@git submodule update --init --recursive
	@cd $(LIBS_DIR)/LibFt/ && git pull

clean:
	@make clean -C $(LIBS_DIR)/LibFT
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBS_DIR)/LibFT
	@rm -f $(NAME)

re: fclean all

.PHONY: all re run clean fclean
