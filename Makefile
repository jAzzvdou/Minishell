NAME	=	minishell

# Lista de arquivos fonte
SRCS	=	main.c              \
		signals.c               \
		token/tokenizator.c     \
		token/check_tokens.c    \
		builtins/cd.c           \
		builtins/builtins.c     \
		builtins/env.c          \
		builtins/pwd.c          \
		builtins/exit.c         \
		builtins/export.c       \
		builtins/echo.c         \
		builtins/unset.c        \
		errors.c        \
		heredoc.c       \
		cleaners.c      \
		parser_utils/number.c        \
		parser_utils/space.c         \
		parser_utils/quote.c         \
		parser_utils/parenthesis.c   \
		parser_utils/spliter.c       \
		parser_utils/split_input.c   \
		utils/utils1.c        \
		utils/utils2.c

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
