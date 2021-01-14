# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 09:55:06 by judecuyp          #+#    #+#              #
#    Updated: 2021/01/12 09:55:06 by judecuyp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
HEADER_PATH = ./includes
SRCS = srcs/main.c srcs/ft_init.c srcs/ft_utils.c srcs/ft_print.c  \
		srcs/ft_states.c srcs/ft_lib.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
			@echo "Compiling $@"
			@$(CC) $(CFLAGS) $(OBJS) -o $@ -I $(HEADER_PATH) -lpthread -lrt
			@echo "Success"
.c.o:
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)

clean:
	@echo "Removing .o"
	@$(RM) $(OBJS)

fclean:	clean
		@echo "Removing Philo"
		@$(RM) $(NAME)

re: fclean all

rec: fclean all
	@echo "Removing .o"
	@$(RM) $(OBJS)

.PHONY: all clean fclean re rec
