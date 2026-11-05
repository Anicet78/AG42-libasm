NASM		= nasm
NASMFLAGS	= -f elf64 -g -F dwarf

SRC_DIR		= ./srcs
OBJ_DIR		= ./objs

SRCS		= ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s ft_calloc.s
OBJS		= $(patsubst %.s, $(OBJ_DIR)/%.o, $(SRCS))

BONUS_SRCS	= ft_atoi_base_bonus.s
BONUS_OBJS	= $(patsubst %.s, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

TEST_SRCS	= test.c

NAME		= libasm.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

test: $(OBJS) $(BONUS_OBJS)
	gcc $(OBJS) $(BONUS_OBJS) $(TEST_SRCS) -g3 -o test

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus test clean fclean re test
