# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/26 16:03:23 by marvin            #+#    #+#              #
#    Updated: 2020/03/26 16:03:23 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER_PATH = ./includes
SRCS = srcs/main.c srcs/ft_utils.c srcs/ft_print.c srcs/ft_init.c \
		srcs/ft_states.c srcs/ft_lib.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
			@echo "Compiling $@"
			@$(CC) $(CFLAGS) $(OBJS) -o $@ -I $(HEADER_PATH) -lpthread
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
