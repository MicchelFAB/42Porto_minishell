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
RDLINE		:= -lreadline -lXext -lX11 -lm
MAKEFLAGS	+= --no-print-directory
MKDIR_P		:= mkdir -p

# ------- PATHS ------- #
INCLUDE		=	-I ./inc/\
				-I ./libft/

# ------- PROJECT ------- #
NAME		:= minishell

# ------- SOURCES ------- #
SRC_DIR		:= src/
LEXER_DIR	:= lexer
SRC_LIB		:= src/libft
SRCS		:= main.c utils.c ft_env.c 
SRC_LEXER	:= ft_lexer.c ft_split_lexer.c

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
SRC_LEXER	:= $(SRC_LEXER:%=$(LEXER_DIR)/%)

BUILD_DIR	:= .build
LIBFT		:= $(BUILD_DIR)/libs/libft.a
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/obj/%.o)
OBJS		+= $(SRC_LEXER:$(LEXER_DIR)/%.c=$(BUILD_DIR)/obj/%.o)
DEPS		:= $(OBJS:.o=.d)

# ------- RULES ------- #
# ------- ALL ------- #
all: $(NAME)

# ------- $(NAME) ------- #
$(NAME): $(OBJS)
	@make -C $(SRC_LIB)
	@cp $(SRC_LIB)/libft.a $(LIBFT)
	@printf "\e[2K\r$(GREEN)Generated $(NAME)$(END)\n"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) $(RDLINE) -o $(NAME)

# ------- OBJECTS ------- #
$(BUILD_DIR)/obj/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@printf "\e[2K\r$(YELLOW)Compiling $<$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(RDLINE) -c $< -o $@ $(INCLUDE)

$(BUILD_DIR)/obj/%.o: $(LEXER_DIR)/%.c | $(BUILD_DIR)
	@printf "\e[2K\r$(YELLOW)Compiling $<$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(RDLINE) -c $< -o $@ $(INCLUDE)
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
	@valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=readline_supression ./$(NAME)

# ------- RECORD LOG ------- #
log: all
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --suppressions=readline_supression --log-file=log%p.txt ./$(NAME)

.PHONY: clean fclean re all bonus leak log