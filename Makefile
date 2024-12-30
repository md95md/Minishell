# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 10:41:49 by plesukja          #+#    #+#              #
#    Updated: 2024/12/30 10:48:23 by plesukja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
## MAC
CC = cc -fsanitize=address
# ## original
# CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/Cellar/readline/8.2.13/include
CFLAGS = -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.2.13/include -v
# ## LINUX
# CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/
LIBFT_A = $(LIBFT)libft.a
HEAD = includes
SRCDIR = srcs
BINDIR = bin

SRCS = libft/get_next_line/get_next_line_bonus.c \
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
				src/execute/builtins/exit.c \
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

OBJS = $(SRCS:%.c=$(BINDIR)/%.o)

## Mac readline
# ## original
#MAC_READ_LINE = -I/opt/homebrew/Cellar/readline/8.2.13/include -L/opt/homebrew/Cellar/readline/8.2.13/lib -lreadline
MAC_READ_LINE = -I/usr/local/Cellar/readline/8.2.13/include -L/usr/local/Cellar/readline/8.2.13/lib -lreadline -lcurse
# ## to find homebrew path
#brew list readline

all: $(NAME)

# MAC
$(NAME): $(OBJS) $(HEAD)/minishell.h $(LIBFT_A) Makefile
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MAC_READ_LINE) -I $(HEAD) -o $@ -v
# #Linux 
# $(NAME): $(OBJS) $(HEAD)/minishell.h $(LIBFT_A) Makefile
# 	$(CC) $(CFLAGS) -lreadline -I $(HEAD) $(OBJS) $(LIBFT_A) -o $@

$(LIBFT_A):
	make -C $(LIBFT)

$(OBJS): $(BINDIR)%.o: $(SRCDIR)/%.c $(HEAD)/minishell.h $(LIBFT_A) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -I $(HEAD) -I$(LIBFT)/$(HEAD) $< -o $@
# $(CC) $(CFLAGS) -c -I $(HEAD) -I$(LIBFT)/$(HEAD) $< -o $@

clean:
	rm -rf $(BINDIR)
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
