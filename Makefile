# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-dana <tel-dana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 19:11:19 by tel-dana          #+#    #+#              #
#    Updated: 2022/12/08 15:37:44 by tel-dana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server

CLIENT = client

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = 	src/client.c src/server.c

OBJ = $(SRCS:%c=%o)

all : $(SERVER) $(CLIENT)

$(SERVER) : src/server.o include/minitalk.h
	@echo "Compiling server"
	@echo ""
	$(CC) src/server.o -o server
	@echo ""

$(CLIENT) : src/client.o include/minitalk.h
	@echo "Compiling client"
	$(CC) src/client.o -o client
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf *.out *.exe server client ./objs ./bin ./libft/src/*.o 
	@echo ""
	@echo "Your shit is clean!"
	@echo ""
re:	fclean all
