NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

MANDATORY_SRCS_DIR = mandatory
BONUS_SRCS_DIR = bonus
LIB_SRCS_DIR = lib

INCLUDES_DIR = includes


MANDATORY_SRCS =	$(MANDATORY_SRCS_DIR)/main.c \
                	$(MANDATORY_SRCS_DIR)/pipex.c \
                	$(MANDATORY_SRCS_DIR)/errors_handling.c \
                	$(MANDATORY_SRCS_DIR)/paths.c \
					$(MANDATORY_SRCS_DIR)/ft_free.c 

BONUS_SRCS =	$(BONUS_SRCS_DIR)/main_bonus.c \
				$(BONUS_SRCS_DIR)/init_datas_bonus.c \
				$(BONUS_SRCS_DIR)/pipe_utils_bonus.c \
				$(BONUS_SRCS_DIR)/pipex_bonus.c \
            	$(BONUS_SRCS_DIR)/get_cmd_bonus.c \
            	$(BONUS_SRCS_DIR)/errors_bonus.c \
				$(BONUS_SRCS_DIR)/free_bonus.c


LIB_SRCS =		$(LIB_SRCS_DIR)/ft_free_str.c \
				$(LIB_SRCS_DIR)/ft_split.c \
				$(LIB_SRCS_DIR)/ft_strchr.c \
				$(LIB_SRCS_DIR)/ft_strdup.c \
				$(LIB_SRCS_DIR)/ft_strjoin.c \
				$(LIB_SRCS_DIR)/ft_strlen.c \
				$(LIB_SRCS_DIR)/ft_strncmp.c \
				$(LIB_SRCS_DIR)/ft_strstr.c \
				$(LIB_SRCS_DIR)/get_next_line.c \
				$(LIB_SRCS_DIR)/get_next_line_utils.c 

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

MANDATORY_HEADERS = $(INCLUDES_DIR)/pipex.h
BONUS_HEADERS = $(INCLUDES_DIR)/pipex_bonus.h
LIB_HEADERS = $(INCLUDES_DIR)/minilibft.h

all: $(NAME)

$(NAME): $(LIB_OBJS) $(MANDATORY_OBJS) 
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)$(NAME) created! (mandatory)$(DEFAULT)\n"

bonus: $(LIB_OBJS) $(BONUS_OBJS) 
	@$(CC) $(CFLAGS) -o $(NAME) $^
	@printf "$(GREEN)$(NAME) created! (bonus)$(DEFAULT)\n"

%.o: %.c $(LIB_HEADERS) $(MANDATORY_HEADERS) $(BONUS_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES_DIR)

clean:
	@rm -f $(LIB_OBJS) $(MANDATORY_OBJS) $(BONUS_OBJS)
	@printf "$(YELLOW)object files deleted!$(DEFAULT)\n"

fclean:
	@$(MAKE) clean --no-print-directory
	@rm -f $(NAME) $(BONUS_NAME)
	@printf "$(RED)all deleted!$(DEFAULT)\n"

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
