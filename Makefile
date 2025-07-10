# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 15:02:56 by alvanaut          #+#    #+#              #
#    Updated: 2025/07/08 14:21:08 by alvanaut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
	   parsing.c \
	   init.c \
	   create_thread.c \
	   destroy.c \
	   print.c \
	   routine.c \
	   create_thread2.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
