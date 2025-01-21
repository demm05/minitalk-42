CLIENT = client
SERVER = server

HDIR = include
ODIR = objs

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I $(HDIR)

LIB_DIR				=	libft
MAKE_LIB			=	@make --no-print-directory -C

PRINTF_DIR			=	$(LIB_DIR)/printf
PRINTF_FILE			=	printf.a
PRINTF				=	$(PRINTF_DIR)/$(PRINTF_FILE)
CFLAGS				+=	-I$(PRINTF_DIR)/include
LIB					+=	$(PRINTF)

C_SRCS := srcs/client.c
S_SRCS := srcs/server.c

C_OBJS := $(patsubst srcs/%.c, $(ODIR)/%.o, $(C_SRCS))
S_OBJS := $(patsubst srcs/%.c, $(ODIR)/%.o, $(S_SRCS))

DIRS = $(ODIR)

all: $(CLIENT) $(SERVER)

$(DIRS):
	@mkdir -p $@

$(CLIENT): $(LIB) $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) $(LIB) -o $@

$(SERVER): $(LIB) $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) $(LIB) -o $@

$(ODIR)/%.o: srcs/%.c | $(DIRS)
	$(CC) $(CFLAGS) -c -o $@ $<

bonus: all

$(PRINTF):
	$(MAKE_LIB) $(PRINTF_DIR)

lib_clean:
	$(MAKE_LIB) $(PRINTF_DIR) clean

lib_fclean:
	$(MAKE_LIB) $(PRINTF_DIR) fclean

directories:
	$(shell mkdir -p $(ODIR))

clean: lib_clean
	@rm -rf $(ODIR)

fclean: clean lib_fclean 
	@rm -rf $(CLIENT) $(SERVER)

re: fclean $(LIB) all

.PHONY: all bonus clean fclean re directories 
