NAME	=	minishell

SRCS	=	main.c                       \
		printers.c                   \
		Builtins/cd.c                \
		Builtins/cd_utils.c          \
		Builtins/builtins.c          \
		Builtins/env.c               \
		Builtins/pwd.c               \
		Builtins/exit.c              \
		Builtins/export_utils.c      \
		Builtins/export.c            \
		Builtins/echo.c              \
		Builtins/unset.c             \
		Cleaners/cleaners.c          \
		Cleaners/free_everything.c   \
		Errors/error_exit.c          \
		Errors/errors.c              \
		Execution/exe.c              \
		Execution/make_if.c          \
		Execution/make_pipe.c        \
		Execution/make_redir.c       \
		Execution/re_exec.c          \
		Execution/controller.c       \
		Expansion/expander.c         \
		Expansion/expander_utils.c   \
		Expansion/split_variable.c   \
		Expansion/split_bonus.c      \
		Expansion/wildcard.c         \
		Heredoc/heredoc.c            \
		Parser/Tokens/tokenizator.c  \
		Parser/Tokens/check_tokens.c \
		Parser/Tokens/space.c        \
		Parser/Tokens/quote.c        \
		Parser/Tokens/parenthesis.c  \
		Parser/Tokens/spliter.c      \
		Parser/Tokens/split_input.c  \
		Parser/Tree/tree.c           \
		Parser/Tree/is_type.c        \
		Parser/Tree/list_functions.c \
		Signals/signals.c            \
		Utils/ft_itoa.c              \
		Utils/number.c               \
		Utils/utils1.c               \
		Utils/utils2.c               \
		Utils/utils3.c

OBJDIR	=	Objects

OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra -ggdb3

RLFLAG	=	-lreadline

RM	=	rm -rf

TOTAL_SRCS	=	$(words $(SRCS))

COMPILED_SRCS	=	0

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) -o $(NAME) $(OBJS) $(RLFLAG)
		@echo "\033[1;97m🔔 Minishell Is Ready! 🔔\033[0m"

$(OBJDIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
		$(eval COLOR_VALUE=$(shell echo $$((255*$(COMPILED_SRCS)/$(TOTAL_SRCS)))))
		@echo -n "\033[38;2;$(COLOR_VALUE);$(COLOR_VALUE);$(COLOR_VALUE)m  Minishell Is Ready!\033[0m\r"
		@sleep 0.01

supp: re
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=Suppression/readline.supp ./minishell

clean:
		@$(RM) $(OBJDIR)
		@echo "\033[38;2;255;165;0m🗑️  Objects Are Cleaned! 🗑️\033[0m"

fclean: clean
		@$(RM) $(NAME)
		@echo "\033[31m🗑️  Minishell Is Cleaned! 🗑️\033[0m"

re: fclean all

.PHONY: all clean fclean re
