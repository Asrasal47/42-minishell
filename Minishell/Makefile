# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 12:50:27 by arasal            #+#    #+#              #
#    Updated: 2023/04/15 16:16:52 by arasal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler Variables
NAME        = minishell

CC          = cc
CFLAGS      = -I -Wall -Wextra -Werror

LIBFT		= ./Libft
LDFLAGS     = -lreadline -L ~/.brew/opt/readline/lib
				
SRCS_B		= ./builtins/builtin.c ./builtins/echo.c ./builtins/exit.c ./builtins/unset.c\
				./builtins/cd.c ./builtins/export.c ./builtins/env.c ./builtins/pwd.c

SRCS_E		= ./execution/simple_cmds.c ./execution/pipe_cmds.c ./execution/op_redirections.c\
				./execution/exec.c ./execution/cmd_fix.c ./execution/path.c ./execution/here_doc.c\
				./execution/here_doc_utils.c ./execution/ip_redirections.c\

SRCS_GNL	= ./get_next_line/get_next_line_bonus.c ./get_next_line/get_next_line_utils_bonus.c

SRCS_P		= ./parsing/parsing.c ./parsing/tokenization.c ./parsing/verify.c ./parsing/quotes.c\
				./parsing/var_expansion.c ./parsing/var_expansion_utils.c

SRCS_U		= ./utils/str_utils.c ./utils/utils.c ./utils/test.c ./utils/error.c

SRCS        = main.c $(SRCS_B) $(SRCS_E) $(SRCS_GNL) $(SRCS_P) $(SRCS_U)

OBJS        = $(SRCS:%.c=%.o)


# **************************************************************************** #
#   RULES                                                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS) 
	-@$(MAKE) --silent -C $(LIBFT)
	-@$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/libft.a -o $@ $(LDFLAGS)
	@echo "$(BOLD)\033[32m\nminishell is compiled! ༺ (\033[31m♥\033[32m_\033[31m♥\033[32m)༻\n"

clean:
	@$(MAKE) --silent -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(BOLD)\033[32m\nEverything is fcleaned! ✓ (\033[31m>_<\033[32m)\n"

re: fclean all

.PHONY: all clean fclean re
