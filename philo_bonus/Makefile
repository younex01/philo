# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/28 05:30:37 by yelousse          #+#    #+#              #
#    Updated: 2022/08/28 05:30:38 by yelousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c ft_atoi.c monitor.c philo_utils.c 
OBJS = ${SRC:.c=.o}
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "Compiling Successfull"

%.o: %.c philo.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "Object Files Removed Successfully"

fclean: clean
	@$(RM) $(NAME)
	@echo "Clear"

re: fclean all

.PHONY : all clean fclean re