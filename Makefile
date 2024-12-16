#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC        := cc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      libft/get_next_line/get_next_line_bonus.c \
                          libft/get_next_line/get_next_line.c \
                          libft/get_next_line/get_next_line_utils.c \
                          libft/get_next_line/get_next_line_utils_bonus.c \
                          libft/libft/ft_bzero.c \
                          libft/libft/ft_memcpy.c \
                          libft/libft/ft_strrchr.c \
                          libft/libft/ft_isascii.c \
                          libft/libft/ft_isdigit.c \
                          libft/libft/ft_memchr.c \
                          libft/libft/ft_striteri.c \
                          libft/libft/ft_isalpha.c \
                          libft/libft/ft_strtrim.c \
                          libft/libft/ft_lstadd_back_bonus.c \
                          libft/libft/ft_substr.c \
                          libft/libft/ft_lstsize_bonus.c \
                          libft/libft/ft_strlen.c \
                          libft/libft/ft_lstmap_bonus.c \
                          libft/libft/ft_tolower.c \
                          libft/libft/ft_putstr_fd.c \
                          libft/libft/ft_toupper.c \
                          libft/libft/ft_lstnew_bonus.c \
                          libft/libft/ft_memcmp.c \
                          libft/libft/ft_strjoin.c \
                          libft/libft/ft_strnstr.c \
                          libft/libft/ft_split.c \
                          libft/libft/ft_putnbr_fd.c \
                          libft/libft/ft_strdup.c \
                          libft/libft/ft_lstadd_front_bonus.c \
                          libft/libft/ft_strlcat.c \
                          libft/libft/ft_lstiter_bonus.c \
                          libft/libft/ft_itoa.c \
                          libft/libft/ft_putendl_fd.c \
                          libft/libft/ft_isalnum.c \
                          libft/libft/ft_strncmp.c \
                          libft/libft/ft_isprint.c \
                          libft/libft/ft_strlcpy.c \
                          libft/libft/ft_lstclear_bonus.c \
                          libft/libft/ft_strchr.c \
                          libft/libft/ft_memmove.c \
                          libft/libft/ft_putchar_fd.c \
                          libft/libft/ft_memset.c \
                          libft/libft/ft_atoi.c \
                          libft/libft/ft_calloc.c \
                          libft/libft/ft_strmapi.c \
                          libft/libft/ft_lstlast_bonus.c \
                          libft/libft/ft_lstdelone_bonus.c \
                          libft/ft_printf/ft_printf_utils.c \
                          libft/ft_printf/ft_printf.c \
                          src/execute/builtins/export.c \
                          src/execute/builtins/echo.c \
                          src/execute/builtins/pwd.c \
                          src/execute/builtins/unset.c \
                          src/execute/builtins/env.c \
                          src/execute/builtins/cd.c \
                          src/execute/builtins/_exit.c \
                          src/execute/builtins/export_no_var.c \
                          src/execute/builtins/export_with_var.c \
                          src/execute/builtins/run_builtin.c \
                          src/execute/execute.c \
                          src/execute/environment.c \
                          src/execute/run_input.c \
                          src/parser/create_token.c \
                          src/parser/process_token.c \
                          src/parser/create_redir_token_heredoc.c \
                          src/parser/parse_token.c \
                          src/parser/procure_token_sign.c \
                          src/signal.c \
                          src/main.c \
                          src/utils.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      libft/get_next_line/get_next_line_bonus.c \
                          libft/get_next_line/get_next_line.c \
                          libft/get_next_line/get_next_line_utils.c \
                          libft/get_next_line/get_next_line_utils_bonus.c \
                          libft/libft/ft_bzero.c \
                          libft/libft/ft_memcpy.c \
                          libft/libft/ft_strrchr.c \
                          libft/libft/ft_isascii.c \
                          libft/libft/ft_isdigit.c \
                          libft/libft/ft_memchr.c \
                          libft/libft/ft_striteri.c \
                          libft/libft/ft_isalpha.c \
                          libft/libft/ft_strtrim.c \
                          libft/libft/ft_lstadd_back_bonus.c \
                          libft/libft/ft_substr.c \
                          libft/libft/ft_lstsize_bonus.c \
                          libft/libft/ft_strlen.c \
                          libft/libft/ft_lstmap_bonus.c \
                          libft/libft/ft_tolower.c \
                          libft/libft/ft_putstr_fd.c \
                          libft/libft/ft_toupper.c \
                          libft/libft/ft_lstnew_bonus.c \
                          libft/libft/ft_memcmp.c \
                          libft/libft/ft_strjoin.c \
                          libft/libft/ft_strnstr.c \
                          libft/libft/ft_split.c \
                          libft/libft/ft_putnbr_fd.c \
                          libft/libft/ft_strdup.c \
                          libft/libft/ft_lstadd_front_bonus.c \
                          libft/libft/ft_strlcat.c \
                          libft/libft/ft_lstiter_bonus.c \
                          libft/libft/ft_itoa.c \
                          libft/libft/ft_putendl_fd.c \
                          libft/libft/ft_isalnum.c \
                          libft/libft/ft_strncmp.c \
                          libft/libft/ft_isprint.c \
                          libft/libft/ft_strlcpy.c \
                          libft/libft/ft_lstclear_bonus.c \
                          libft/libft/ft_strchr.c \
                          libft/libft/ft_memmove.c \
                          libft/libft/ft_putchar_fd.c \
                          libft/libft/ft_memset.c \
                          libft/libft/ft_atoi.c \
                          libft/libft/ft_calloc.c \
                          libft/libft/ft_strmapi.c \
                          libft/libft/ft_lstlast_bonus.c \
                          libft/libft/ft_lstdelone_bonus.c \
                          libft/ft_printf/ft_printf_utils.c \
                          libft/ft_printf/ft_printf.c \
                          src/execute/builtins/export.c \
                          src/execute/builtins/echo.c \
                          src/execute/builtins/pwd.c \
                          src/execute/builtins/unset.c \
                          src/execute/builtins/env.c \
                          src/execute/builtins/cd.c \
                          src/execute/builtins/_exit.c \
                          src/execute/builtins/export_no_var.c \
                          src/execute/builtins/export_with_var.c \
                          src/execute/builtins/run_builtin.c \
                          src/execute/execute.c \
                          src/execute/environment.c \
                          src/execute/run_input.c \
                          src/parser/create_token.c \
                          src/parser/process_token.c \
                          src/parser/create_redir_token_heredoc.c \
                          src/parser/parse_token.c \
                          src/parser/procure_token_sign.c \
                          src/signal.c \
                          src/main.c \
                          src/utils.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
