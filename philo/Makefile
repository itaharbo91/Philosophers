# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 12:56:27 by itaharbo          #+#    #+#              #
#    Updated: 2025/05/17 22:08:37 by itaharbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC= cc
I= -I srcs -I includes
CFLAGS= -Wall -Wextra -Werror -pthread $(I)
SRCS=	srcs/actions/action_log.c srcs/actions/eating.c srcs/actions/monitor.c srcs/actions/routine.c	\
			srcs/cleanup/cleanup.c	\
				srcs/init_prog/parsing_arg.c srcs/init_prog/philos.c srcs/init_prog/simulation_status.c srcs/init_prog/threads.c	\
					srcs/main/main.c	\
						srcs/utils/utils.c
OBJ_DIR= objs
OBJS= $(addprefix $(OBJ_DIR)/, $(SRCS:srcs/%.c=%.o))

all: $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Linking $(OBJS) -> $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) has been successfully created!"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "Cleaning object files..."; \
		rm -rf $(OBJ_DIR); \
	else \
		echo "No object files to clean."; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "Removing $(NAME)..."; \
		rm -f $(NAME); \
		echo "$(NAME) has been successfully removed!"; \
	else \
		echo "$(NAME) does not exist."; \
	fi

re: fclean all

.PHONY: all clean fclean re
