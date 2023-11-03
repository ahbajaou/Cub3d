# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 07:18:20 by himejjad          #+#    #+#              #
#    Updated: 2023/11/03 08:30:28 by himejjad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
SRC1 = main.c parsing.c get_map.c utls_parse.c get_next_line_utils.c get_next_line.c textures.c

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o

all: ${NAME}

OBJS = ${SRC1:.c=.o}
%.o: %.c
	$(CC) ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

${NAME}: ${OBJS}
	@$(CC) ${FLAGS} ${OBJS} ${MLX} ${NAME}
	@echo "all's ready"

clean:
	@rm -f ${OBJS}
	@echo "all's clean"

fclean: clean
	@rm -f ${NAME}

re: fclean all
