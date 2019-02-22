# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thgiraud <thgiraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 17:47:51 by thgiraud          #+#    #+#              #
#    Updated: 2019/02/22 16:01:43 by jcorwin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rtv1

SRC		= main.c \
		  sdl_frame.c \
		  vector.c \
		  vector2.c \
		  render.c \
		  parser.c \
		  parser2.c \
		  parser3.c \
		  parser4.c \
		  get_next_line.c \
		  intersection_with_cone.c \
		  intersection_with_sphere.c \
		  intersection_with_cylinder.c \
		  light.c \
		  quaternion_1.c \
		  quaternion_2.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# mlx library
MLX		= /usr/local/lib
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I /usr/local/include
MLX_LNK	= -L /usr/local/lib -l mlx -framework OpenGL -framework AppKit

# SDL library
SDL_INC = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers
SDL_LNK = -F ~/Library/Frameworks/ -framework SDL2

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft/includes
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./objects/

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(SDL_INC) $(FT_INC) -I $(INCDIR) $(FT_INC) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(SDL_LNK) -framework OpenCL $(FT_LNK) -framework OpenCL -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all
