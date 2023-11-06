# ------- FONT AND COLORS ------- #
GREY		:= \e[1;30m
RED			:= \e[1;31m
GREEN		:= \e[1;32m
YELLOW		:= \e[1;33m
BLUE		:= \e[1;34m
MAGENTA		:= \e[1;35m
CYAN		:= \e[1;36m
WHITE		:= \e[1;37m

BOLD		:= \e[1m
DIM			:= \e[2m	
UNDERLINE	:= \e[4m
BLINK		:= \e[5m
INVERTED	:= \e[7m
END			:= \e[0m

# ------- COMMANDS ------- #

CC			:= cc
RM			:= rm -rf

# ------- FLAGS ------- #
CFLAGS		:= -Wall -Wextra -Werror -g
CPPFLAGS	:= -MMD -MP
RDLINE		:= -lreadline
MAKEFLAGS	+= --no-print-directory
MKDIR_P		:= mkdir -p

# ------- PATHS ------- #
INCLUDE		=	-I ./inc/\
				-I ./libft/

# ------- PROJECT ------- #
NAME		:= minishell

# ------- SOURCES ------- #
SRC_DIR		:= src

BUILTIN_DIR	:= builtin
LEXER_DIR	:= lexer
PARSE_DIR	:= parse
SRC_LIB		:= src/libft

SRCS		:=	main.c \
				clean.c ft_free.c ft_signals.c\
				ft_env.c ft_env_utils.c utils.c ft_exp.c 

SRC_BUILTIN	:=  echo_cmd.c \
				pwd_cmd.c \
				cd_cmd.c \
				exit_cmd.c exit_cmd_utils.c \
				export_cmd.c export_cmd_utils.c \
				unset_cmd.c \
				builtin.c builtin_utils.c

SRC_LEXER	:=	ft_lexer.c ft_split_lexer.c ft_expander.c ft_quoting.c \
				ft_expander_utils.c ft_especial.c

SRC_PARSE	:=	parse.c parse_utils.c execute.c execute_utils.c \
				execute_utils2.c ft_redirects.c ft_heredoc.c

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
SRC_BUILTIN	:= $(SRC_BUILTIN:%=$(BUILTIN_DIR)/%)
SRC_LEXER	:= $(SRC_LEXER:%=$(LEXER_DIR)/%)
SRC_PARSE	:= $(SRC_PARSE:%=$(PARSE_DIR)/%)

BUILD_DIR	:= .build
LIBFT		:= $(BUILD_DIR)/libs/libft.a
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/obj/%.o)
OBJS		+= $(SRC_BUILTIN:$(BUILTIN_DIR)/%.c=$(BUILD_DIR)/obj/%.o)
OBJS		+= $(SRC_LEXER:$(LEXER_DIR)/%.c=$(BUILD_DIR)/obj/%.o)
OBJS		+= $(SRC_PARSE:$(PARSE_DIR)/%.c=$(BUILD_DIR)/obj/%.o)
DEPS		:= $(OBJS:.o=.d)

# ------- RULES ------- #
# ------- ALL ------- #
all: $(NAME)

# ------- $(NAME) ------- #
$(NAME): $(OBJS)
	@make -C $(SRC_LIB)
	@cp $(SRC_LIB)/libft.a $(LIBFT)
	@printf "\e[2K\r$(GREEN)Generated $(NAME)$(END)\n"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(RDLINE) $(OBJS) $(LIBFT) -o $(NAME)

# ------- OBJECTS ------- #
$(BUILD_DIR)/obj/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@printf "\e[2K\r$(YELLOW)Compiling $<$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(INCLUDE)

$(BUILD_DIR)/obj/%.o: $(BUILTIN_DIR)/%.c | $(BUILD_DIR)
	@printf "\e[2K\r$(YELLOW)Compiling $<$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -O3 $< -o $@ $(INCLUDE)

$(BUILD_DIR)/obj/%.o: $(LEXER_DIR)/%.c | $(BUILD_DIR)
	@printf "\e[2K\r$(YELLOW)Compiling $<$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(INCLUDE)

$(BUILD_DIR)/obj/%.o: $(PARSE_DIR)/%.c | $(BUILD_DIR)
	@printf "\e[2K\r$(YELLOW)Compiling $<$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(INCLUDE)

# ------- DEPS ------- #
-include $(DEPS)

# ------- BUILD_DIR ------- #
$(BUILD_DIR):
	@$(MKDIR_P) $(BUILD_DIR)/libs $(BUILD_DIR)/obj

# ------- CLEAN ------- #
clean:
	@printf "\e[2K\r$(RED)Cleaning objects from $(NAME)$(END)\n"
	@make -C $(SRC_LIB) clean
	@$(RM) $(OBJS) $(DEPS) $(BUILD_DIR)

# ------- FCLEAN ------- #
fclean: clean
	@printf "\e[2K\r$(RED)Cleaning executables from $(NAME)$(END)\n"
	@make -C $(SRC_LIB) fclean
	@$(RM) $(NAME)

# ------- RE ------- #
re:
	@$(MAKE) fclean
	@$(MAKE) all

# ------- TEST LEAKS ------- #
leak: all
	@valgrind -q --leak-check=full --show-leak-kinds=all \
		--suppressions=readline_supression --track-fds=yes ./$(NAME)

# ------- RECORD LOG ------- #
log: all
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all \
		--suppressions=readline_supression --log-file=log%p.txt ./$(NAME)

.PHONY: clean fclean re all bonus leak log
