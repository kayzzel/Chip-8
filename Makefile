#------------------------------- VARIABLES ----------------------------------#

NAME			=	chip-8
CC				=	cc

#-------------------------------- DIRECTORIES --------------------------------#


INCLUDE_DIR		=	includes/
UTILS_DIR		=	utils/

SRC_DIR			=	src/
OBJ_DIR			=	.build/

#-------------------------------- INCLUDES & FLAGS ---------------------------#

INCLUDES		= -I $(INCLUDE_DIR)
CFLAGS			=	-Wall -Wextra -Werror
MAKEFLAGS		+=	-j $$(nproc) 
DEPS			=	-MMD -MP

#-------------------------------- SOURCE FILES -------------------------------#

UTILS_SRCS				:=	$(addprefix $(UTILS_DIR), \
							files_utils.c \
							print_utils.c \
							time_utils.c \
							)

OPCODE_SRC		:=	opcode/opcode_select.c

MAIN_SRCS		:=	main.c \
					loading.c \
					screen.c \
					keypad.c

SRCS			:=	$(addprefix $(SRC_DIR), \
					$(MAIN_SRCS) \
					$(OPCODE_SRC) \
					$(UTILS_SRCS) \
					)

#-------------------------------- OBJECTS ------------------------------------#

OBJS			=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
DEPENDENCIES	=	$(OBJS:.o=.d)

#-------------------------------- RULES --------------------------------------#


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)  $(LDFLAGS)

$(OBJ_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEPS) -c $< -o $@

test: fclean
	@$(MAKE) $(NAME) SRCS="$(TESTS_SRCS)" --no-print-directory

clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)


re: fclean
	$(MAKE) all

compile_flags:
	@echo "-I./$(INCLUDE_DIR)" > compile_flags.txt
	@echo "$(CFLAGS)" | tr ' ' '\n' >> compile_flags.txt
	@echo "Generating compile_flags.txt done"

-include $(DEPENDENCIES)

.PHONY: all clean fclean re print-% test
