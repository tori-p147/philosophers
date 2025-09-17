NAME = philo

SRC_DIR = src
INC_DIR = includes
BLD_DIR = obj

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -pthread
COPY = cp
RM = rm -rf
INCLUDES  = -I$(INC_DIR)

SRC_FILES = main.c \
		validation_utils.c \
		init.c \
		routine.c \
		free_utils.c \
		support_utils.c

SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o,$(SOURCES))

all: $(NAME)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDES) -o $(NAME)

clean:
	@$(RM) $(BLD_DIR)

fclean:
	@$(RM) $(BLD_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re