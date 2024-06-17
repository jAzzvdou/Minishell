NAME	=	minishell

SRCS	=	main.c                \
		Signals/signals.c     \
		Tokens/tokenizator.c  \
		Tokens/check_tokens.c \
		Builtins/cd.c         \
		Builtins/builtins.c   \
		Builtins/env.c        \
		Builtins/pwd.c        \
		Builtins/exit.c       \
		Builtins/export.c     \
		Builtins/echo.c       \
		Builtins/unset.c      \
		Errors/errors.c       \
		Heredoc/heredoc.c     \
		Cleaners/cleaners.c   \
		Parser/space.c        \
		Parser/quote.c        \
		Parser/parenthesis.c  \
		Parser/spliter.c      \
		Parser/split_input.c  \
		Utils/number.c        \
		Utils/utils1.c        \
		Utils/utils2.c        \
		Utils/utils3.c

OBJDIR  =   Objects

OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra

RLFLAG	=	-lreadline

RM	=	rm -rf

#define color_code
#$(shell echo "\033[38;5;$(1)m")
#endef

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) -o $(NAME) $(OBJS) $(RLFLAG)
		@echo "Minishell Is Ready!"

$(OBJDIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJDIR)
		@echo "Objects Are Cleaned!"

fclean: clean
		@$(RM) $(NAME)
		@echo "Minishell Is Cleaned!"

re: fclean all

.PHONY: all clean fclean re
