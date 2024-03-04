# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 21:58:41 by fcosta-f          #+#    #+#              #
#    Updated: 2024/03/04 22:01:10 by fcosta-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS 	= main.c utils.c validation.c init.c time.c \
			output.c garbage_collector.c mutex.c \
			routine_finish.c routine_dining.c

CC = cc 
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

%.o: %.c philo.h Makefile
		${CC} ${CFLAGS} -c $< -o $@	

OBJS = ${SRCS:.c=.o}

all: 
		$(MAKE) ${NAME}

${NAME}:: ${OBJS} $(LIBFT) Makefile
		${CC} $(CFLAGS) $(OBJS) -o ${NAME}

clean:
		${RM} ${OBJS} 

fclean: clean 
		${RM} ${OBJS} ${NAME}

re: 
		$(MAKE) fclean 
		$(MAKE) all

.PHONY: all clean fclean re