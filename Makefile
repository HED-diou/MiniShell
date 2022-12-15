# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:13:41 by nramadan          #+#    #+#              #
#    Updated: 2022/06/11 15:14:59 by nramadan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cc = gcc
cflags = -Wall -Wextra -Werror
najib =  -lreadline -L /Users/nramadan/goinfre/.brew/opt/readline/lib -I /Users/nramadan/goinfre/.brew/opt/readline/include
hamza =  -lreadline -L /Users/hed-diou/goinfre/.brew/opt/readline/lib -I /Users/hed-diou/goinfre/.brew/opt/readline/include
srcs = parcing/prep_exec.c \
	   parcing/errors.c \
	   parcing/utils.c \
	   parcing/utils2.c \
	   parcing/cut_cmd.c \
	   parcing/ft_split.c \
	   parcing/duplicat_quate.c \
	   parcing/single_quate_error.c \
	   parcing/pipe_fun.c \
	   parcing/set_space.c \
	   parcing/valid_operators.c \
	   parcing/env_var.c \
	   parcing/cut_herdog.c \
	   parcing/cut_catfile.c \
	   parcing/profound_print.c \
	   parcing/free_all.c \
	   parcing/start_parce.c \
	   parcing/parce_errors.c \
	   parcing/open_pipe.c \
	   parcing/var_fun.c \
	   parcing/expand_var.c \
	   parcing/final_touch.c \
	   parcing/utils3.c \
	   parcing/utils4.c \
	   parcing/delete_var.c \
	   parcing/history_funs.c \
	   parcing/herdoc_fun.c \
	   exec/execution.c \
	   exec/linkedlist_funcs/ft_lst_1.c \
	   exec/builtins/envp/envp.c \
	   exec/builtins/pwd/pwd.c \
	   exec/builtins/cd/cd.c \
	   exec/builtins/echo/echo.c \
	   exec/builtins/unset/unset.c \
	   exec/builtins/export/export.c \
	   exec/builtins/export/utils_export1.c \
	   exec/builtins/export/utils_export2.c \
	   exec/builtins/export/utils_export3.c \
	   exec/builtins/export/utils_export4.c \
	   exec/builtins/exit/exit.c \
	   exec/utils_exec/ft_strjoin.c \
	   exec/utils_exec/ft_strtrim.c \
	   exec/utils_exec/ft_strnstr.c \
	   exec/utils_exec/utils_exec1.c \
	   exec/utils_exec/utils_exec2.c \
	   exec/utils_exec/utils_exec3.c \

obj = ${srcs:.c=.o}

NAME = minishell

lib = minishell.a

.c.o :
	@-@$(cc) $(cflags) -c $< -o $@
	@-ar -rcs $(lib) $@

all : $(NAME)

$(NAME) : $(obj)
	@echo "\033[1;32m[ Executable check ]\033[0m"
	@-@$(cc) $(najib) $(cflags) $(lib) minishell.c -o $(NAME)
	@echo "\033[1;32m[ Executable Updated ]\n\n\n"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "                          by hed-diou && nramadan   -- 1337 (42)   "

clean :
	@echo "\033[1;31m[ Delete Objects files ]\033[0m"
	@-@rm -rf $(lib) $(obj)

fclean : clean
	@echo "\033[1;31m[ Delete Executable ]\033[0m"
	@-rm -rf $(NAME)
re : fclean all
