# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riyano <riyano@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 18:35:13 by riyano            #+#    #+#              #
#    Updated: 2025/05/28 19:15:20 by riyano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = srcs
BUILD_DIR = build

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_FILES = main.c init.c utils.c philo_routines.c threads.c monitor_routines.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
