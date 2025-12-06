# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 12:57:01 by itaharbo          #+#    #+#              #
#    Updated: 2025/05/17 22:27:26 by itaharbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo_bonus

CC= cc
I= -I bonus -I includes
CFLAGS= -Wall -Wextra -Werror -pthread -g $(I)
BONUS=	bonus/actions/action_log_bonus.c bonus/actions/monitor_bonus.c bonus/actions/routine_bonus.c	\
			bonus/cleanup/cleanup_bonus.c	\
				bonus/init_prog/parsing_arg_bonus.c bonus/init_prog/philos_bonus.c bonus/init_prog/semaphores_bonus.c	\
					bonus/main/main_bonus.c	\
						bonus/utils/utils_bonus.c
OBJ_DIR= objs
OBJS= $(addprefix $(OBJ_DIR)/, $(BONUS:bonus/%.c=%.o))

all: $(NAME)

bonus: $(NAME)

$(OBJ_DIR)/%.o: bonus/%.c
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

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
