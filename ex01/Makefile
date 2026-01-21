# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aliberal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 17:09:48 by aliberal          #+#    #+#              #
#    Updated: 2026/01/21 01:33:04 by aliberal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++
RM = rm -rf
NAME = RPN
SRCS = ./srcs/main.cpp ./srcs/RPN.cpp 
DIROBJS = objectos
OBJS = $(addprefix $(DIROBJS)/,$(SRCS:.cpp=.o))
CLEAR = clear

all: $(NAME)

$(NAME): $(OBJS)
	$(CLEAR)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "executed successfully..."

$(DIROBJS)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(CLEAR)
	$(RM) $(DIROBJS)
	@echo "clean executed successfully..."

fclean: clean
	$(CLEAR)
	$(RM) $(NAME)
	@echo "fclean executed successfully..."

re: fclean all

.PHONY: clean fclean all re

.SILENT:
