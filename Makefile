### PROGRAM NAME ###
NAME		:= minishell

### UTILS ###
CC 			:= clang
CFLAGS 		:= -Wall -Wextra -Werror
DEP_FLAGS	:= -MMD -MP
MAKE_FLAG 	:= --no-print-directory --silent
RM 			:= rm -rf

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
GREEN    	:= \033[0;32m
UGREEN    	:= \033[4;32m
YELLOW    	:= \033[;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m
NEW			:= \r\033[K

### DIRECTORIES ###
SRC_DIR 	:= src
INCLD_DIR 	:= include
OBJS_DIR 	:= objs
LIBFT_DIR 	:= libft
EXEC_DIR	:= exec
ENV_DIR		:= env
UTILS_DIR	:= utils
BUILTIN_DIR	:= builtins
PARSING_DIR	:= parsing

### FILES ###
define INCLUDES	:=
	$(INCLD_DIR)/
	$(LIBFT_DIR)/
endef
INCLUDES 	:= $(strip $(INCLUDES))

INCLD_FLAG 	:= $(addprefix -I , $(INCLUDES))
LIBFT		:= $(LIBFT_DIR)/libft.a

define LIB 	:=
	$(LIBFT)
	-lreadline
endef
LIB 		:= $(strip $(LIB))

define SRC 	:=
	$(addprefix $(BUILTIN_DIR)/, \
		cd.c \
		echo.c \
		env.c \
		exit.c \
		export.c \
		pwd.c \
		unset.c
	)
	$(addprefix $(ENV_DIR)/, \
		env_list.c \
		env_path.c
	)
	$(addprefix $(EXEC_DIR)/, \
		here_doc.c \
		pipex_n_cmd.c \
		pipex_one_cmd.c \
		pipex_utils_1.c \
		pipex_utils_2.c \
		process_role.c
	)
	$(addprefix $(UTILS_DIR)/, \
		utils_errors.c \
		utils_struct_pipe.c \
		utils_struct.c \
		utils.c \
		utils_2.c
	)
	$(addprefix $(PARSING_DIR)/, \
		add_error.c \
		add_operator.c \
		add_sep.c \
		add_word.c \
		utils_add.c \
		utils_add_2.c \
	)
	utils_main.c
	main.c
	signal_handler.c
endef
SRC 		:= $(strip $(SRC))

OBJS 		:= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
DEPS		:= $(patsubst %.c,$(OBJS_DIR)/%.d,$(SRC))

### PROJECT ###
.PHONY: all
all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@printf "$(NEW)$(PURPLE)[$(JP)] $(UGREEN)Building:$(DEFAULT)$(BWHITE) $@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INCLD_FLAG) -o $@
	@printf "\n"

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(NEW)$(PURPLE)[$(JP)] $(UGREEN)Building:$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(EXEC_DIR)
	@mkdir -p $(OBJS_DIR)/$(ENV_DIR)
	@mkdir -p $(OBJS_DIR)/$(BUILTIN_DIR)
	@mkdir -p $(OBJS_DIR)/$(UTILS_DIR)
	@mkdir -p $(OBJS_DIR)/$(PARSING_DIR)
	@$(CC) $(DEP_FLAGS) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

.PHONY: clean
clean: ; @printf "$(PURPLE)[$(JP)] $(RED)Removing $(DEFAULT)$(OBJS_DIR) files\n"
	@$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean ; @printf "$(PURPLE)[$(JP)] $(RED)Removing $(DEFAULT)$(NAME)\n"
	@$(RM) $(NAME) 

.PHONY: re
re: fclean all

### LIBFT ###
$(LIBFT):
	@make -C $(LIBFT_DIR) $(MAKE_FLAG)

.PHONY: cleanlib
cleanlib: ; @make -C $(LIBFT_DIR) clean $(MAKE_FLAG)

.PHONY: fcleanlib
fcleanlib: ; @make -C $(LIBFT_DIR) fclean $(MAKE_FLAG)

.PHONY: relib
relib: ; @make -C $(LIBFT_DIR) re $(MAKE_FLAG)

### VALGRIND ###
.PHONY: valshell
valshell: $(NAME)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore_readline.supp ./$(NAME)
