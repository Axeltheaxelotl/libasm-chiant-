# Makefile pour compiler du code assembleur

# Variables
ASM = nasm
ASMFLAGS = -f elf64
LD = ld
CC = gcc
CFLAGS = -Wall -Wextra -Werror -no-pie

# Fichiers
ASM_SRC = ft_strlen.s ft_strcpy.s ft_write.s ft_atoi_base.s ft_strdup.s ft_read.s ft_list_size.s ft_list_push_front.s
C_SRC = main.c
ASM_OBJ = $(ASM_SRC:.s=.o)
C_OBJ = $(C_SRC:.c=.o)
NAME = test_asm

# Règles
all: $(NAME)

# Compile le fichier assembleur en objet
%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

# Compile le fichier C en objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Lie tout ensemble
$(NAME): $(ASM_OBJ) $(C_OBJ)
	$(CC) $(CFLAGS) $(ASM_OBJ) $(C_OBJ) -o $(NAME)

clean:
	rm -f $(ASM_OBJ) $(C_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
