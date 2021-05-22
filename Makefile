# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 16:00:17 by niduches          #+#    #+#              #
#    Updated: 2021/05/22 16:40:50 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

D_SRC	=	./src/
D_INC	=	./include/

BUILD_DIR = build

SRC	=	$(D_SRC)main.cpp					\
		$(D_SRC)Rubik.cpp					\
		$(D_SRC)color.cpp					\
		$(D_SRC)instruction.cpp				\
		$(D_SRC)display.cpp					\
		$(D_SRC)rotate.cpp					\
		$(D_SRC)utils.cpp					\
		$(D_SRC)matrix.cpp					\
		$(D_SRC)resolve.cpp					\
		$(D_SRC)edge.cpp					\
		$(D_SRC)corner.cpp					\
		$(D_SRC)belge.cpp					\
		$(D_SRC)cross.cpp					\
		$(D_SRC)down_corner.cpp				\
		$(D_SRC)format.cpp					\
		$(D_SRC)graphique.cpp				\
		$(D_SRC)camera.cpp					\
		$(D_SRC)display_window.cpp			\
		$(D_SRC)mesh.cpp					\
		$(D_SRC)obj.cpp						\
		$(D_SRC)shader.cpp					\
		$(D_SRC)graphique_instruction.cpp	\

OBJ	=	$(SRC:%.cpp=$(BUILD_DIR)/%.o)

NAME	=	rubik

CFLAGS	+=	-W -Wall -Wextra -I$(D_INC) -Werror -g

LDFLAGS	= -lm -lGL -lX11 -lSDL2 -lGLEW

all: $(NAME)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(BUILD_DIR)

fclean:
	@$(MAKE) clean
	@rm -f $(NAME)
	@rm -f *~

$(NAME): $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
