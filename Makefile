# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 07:18:20 by himejjad          #+#    #+#              #
#    Updated: 2023/11/09 21:43:35 by himejjad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
# CC =  
SRC1 = main.c parsing.c get_map.c utls_parse.c get_next_line_utils.c get_next_line.c textures.c utls_parse_2.c \
		utls_parse_3.c
FLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3
MLX = -lmlx -framework OpenGL -framework AppKit

all :  ${NAME}

OBJS = ${SRC1:.c=.o}

${NAME} : ${OBJS}
	@cc  ${FLAGS} ${OBJS} ${MLX} -o ${NAME}
	@echo "all's ready"
clean :
	@rm -rf ${OBJS}
	@echo "all's clean"
fclean :clean
	@rm -rf ${NAME}
re :fclean all