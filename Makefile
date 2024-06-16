NAME	=	minishell

# Lista de arquivos fonte
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
		Parser/number.c       \
		Parser/space.c        \
		Parser/quote.c        \
		Parser/parenthesis.c  \
		Parser/spliter.c      \
		Parser/split_input.c  \
		Utils/utils1.c        \
		Utils/utils2.c

# Diretório de saída dos arquivos objeto
OBJDIR  =   obj

# Lista de arquivos objeto com o diretório obj/ prefixado
OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra -ggdb3

RLFLAG	=	-lreadline

RM	=	rm -rf

# Cria o executável a partir dos arquivos objeto
all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) -o $(NAME) $(OBJS) $(RLFLAG)
		@echo "minishell is ready"

# Regra para compilar arquivos .c em .o dentro do diretório obj/
$(OBJDIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos objeto
clean:
		@$(RM) $(OBJDIR)

# Limpa os arquivos objeto e o executável
fclean: clean
		@$(RM) $(NAME)

# Refaz a compilação completa
re: fclean all

.PHONY: all clean fclean re
