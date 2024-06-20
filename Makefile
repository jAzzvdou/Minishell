NAME	=	minishell

SRCS	=	main.c                  \
		debug.c                 \
		Signals/signals.c       \
		Tokens/tokenizator.c    \
		Tokens/check_tokens.c   \
		Builtins/cd.c           \
		Builtins/cd_utils.c     \
		Builtins/builtins.c     \
		Builtins/env.c          \
		Builtins/pwd.c          \
		Builtins/exit.c         \
		Builtins/export_utils.c \
		Builtins/export.c       \
		Builtins/echo.c         \
		Builtins/unset.c        \
		Errors/errors.c         \
		Heredoc/heredoc.c       \
		Cleaners/cleaners.c     \
		Parser/space.c          \
		Parser/quote.c          \
		Parser/parenthesis.c    \
		Parser/spliter.c        \
		Parser/split_input.c    \
		Utils/number.c          \
		Utils/utils1.c          \
		Utils/utils2.c          \
		Utils/utils3.c

OBJDIR	=	Objects

OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra

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
		@sleep 0.1

clean:
		@$(RM) $(OBJDIR)
		@echo "\033[38;2;255;165;0m🗑️  Objects Are Cleaned! 🗑️\033[0m"

fclean: clean
		@$(RM) $(NAME)
		@echo "\033[31m🗑️  Minishell Is Cleaned! 🗑️\033[0m"

re: fclean all

.PHONY: all clean fclean re
