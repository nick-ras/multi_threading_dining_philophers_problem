# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nick <nick@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 10:21:39 by nickras           #+#    #+#              #
#    Updated: 2022/12/02 21:06:18 by nick             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIBFTPRINTF_PATH	= ./libftprintf
LIBFTPRINTF_A	= $(LIBFTPRINTF_PATH)/libftprintf.a

MAKE = make
CC = gcc
RM = rm -rf
CFLAG = -Wall -Werror -Wextra
SRC_DIR = 	./src/
OBJ_DIR =   ./obj/


SRC_FILES = main.c

OBJ_FILES = ${SRC_FILES:.c=.o}
SRC			= $(addprefix $(SRC_DIR),$(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR),$(OBJ_FILES))

${NAME}: ${OBJ} $(LIBFTPRINTF_A)
			${CC} -o ${NAME} ${CFLAG} ${OBJ} ${LIBFTPRINTF_A}
all: ${NAME}

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			$(MAKE) all -C $(LIBFTPRINTF_PATH)
			mkdir -p $(OBJ_DIR)
			${CC} ${CFLAG} -o $@ -c $^

clean:
			$(RM) ${OBJ_DIR}

fclean: clean
			$(RM) ${NAME}
#			make fclean -C $(LIBFTPRINTF_PATH)

re: fclean all

.PHONY: all clean fclean re