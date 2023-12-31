# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 15:17:48 by craimond          #+#    #+#              #
#    Updated: 2023/12/27 15:59:57 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = main.c pipex_logic.c pipex_utils.c string_utils.c
SRCS_BONUS = main_bonus.c pipex_logic.c pipex_utils.c pipex_utils_bonus.c string_utils.c ${addprefix gnl_bonus/, ${addprefix get_next_line, .c _utils.c}}
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
HEADER = pipex.h
HEADER_BONUS = pipex_bonus.h
CMD1 = cw -l
CMD2 = wc -l

$(NAME): $(OBJS) $(HEADER)
	@cc -Wall -Wextra -Werror $(OBJS) -o $(NAME)
	@echo compiled $(NAME)

all: $(NAME)

%.o: %.c 
	@cc -Wall -Wextra -Werror -c $< -o $@

bonus: $(OBJS_BONUS) $(HEADER) $(HEADER_BONUS)
	@cc -Wall -Wextra -Werror $(OBJS_BONUS) -o $(NAME)
	@echo compiled $(NAME) with bonus

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo deleted obj files

fclean: clean
	@rm -rf $(NAME)
	@echo deleted $(NAME)

re: fclean all

debug: $(DOBJS) $(HEADER)
	@gcc -g -Wall -Wextra -Werror $(SRCS) -o $(NAME)
	@echo starting debugger with default input
	@gdb --args ./$(NAME) infile "$(CMD1)" "$(CMD2)" outfile
	@fclean

.PHONY: all clean fclean debug re bonus