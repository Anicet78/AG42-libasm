NASM		= nasm
NASMFLAGS	= -f elf64

SRC_DIR		= ./srcs
OBJ_DIR		= ./objs

SRCS		= ft_strlen.s
OBJS		= $(patsubst %.s, $(OBJ_DIR)/%.o, $(SRCS))

BONUS_SRCS	=
BONUS_OBJS	= $(patsubst %.s, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

NAME		= libasm.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(NASM) $(NASMFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus test clean fclean re
