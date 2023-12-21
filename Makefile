# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 15:17:48 by craimond          #+#    #+#              #
#    Updated: 2023/12/21 15:22:13 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = pipex.c pipex_utils.c general_utils.c
OBJS = ${SRCS:.c=.o}
HEADER = pipex.h
CMD1 = grep hello
CMD2 = wc -l

$(NAME): $(OBJS) $(HEADER)
	@cc -Wall -Wextra -Werror $(OBJS) -o $(NAME);
	@echo compiled $(NAME)

all: $(NAME)

%.o: %.c
	@cc -Wall -Wextra -Werror -c $< -o $@

clean: $(OBJS)
	@rm -rf $(OBJS)
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

.PHONY: all clean fclean debug re