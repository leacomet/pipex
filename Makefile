# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acomet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 16:30:18 by acomet            #+#    #+#              #
#    Updated: 2023/05/03 15:19:53 by acomet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
NAME_BONUS	=	pipex_bonus

LIBFT		=	libft/libft.a
PRINTF		=	ft_printf/libftprintf.a
PRINTFERR	=	ft_printferr/libftprintferr.a

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -g
LDFLAGS		=	-L $(dir $(LIBFT)) -L $(dir $(PRINTF)) -L $(dir $(PRINTFERR))
CPPFLAGS	=	-I libft -I ft_printf -I ft_printferr
LDLIBS		=	-l:libft.a -l:libftprintf.a -l:libftprintferr.a

MAND		=	mandatory
BUILD		=	build
BUILD_BONUS	=	build_bonus
BONUS		=	bonus
GNL			=	get_next_line

SRCS		= 	$(MAND)/pipex.c \
				$(MAND)/ppx_get_path.c \
				$(MAND)/ppx_get_args.c \
				$(MAND)/ppx_forks.c \
				$(MAND)/ppx_infile_outfile.c \
				$(MAND)/ppx_close.c \
				$(MAND)/ppx_free.c \

SRCS_BONUS	=	$(BONUS)/pipex_bns.c \
				$(BONUS)/initialize_bns.c \
				$(BONUS)/ppx_get_path_bns.c \
				$(BONUS)/ppx_get_args_bns.c \
				$(BONUS)/ppx_forks_bns.c \
				$(BONUS)/ppx_infile_outfile_bns.c \
				$(BONUS)/ppx_here_doc_bns.c \
				$(BONUS)/ppx_close_bns.c \
				$(BONUS)/ppx_free_bns.c \
				$(GNL)/get_next_line.c \
				$(GNL)/get_next_line_utils.c \

OBJS 		= 	$(SRCS:$(MAND)/%.c=$(BUILD)/%.o)

OBJS_BONUS	=	$(SRCS_BONUS:$(BONUS)/%.c=$(BUILD_BONUS)/%.o)

all: $(NAME)
.PHONY: all

$(BUILD)/%.o: $(MAND)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(BUILD) $(OBJS) $(LIBFT) $(PRINTF) $(PRINTFERR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(dir $(LIBFT))

$(PRINTF):
	$(MAKE) -C $(dir $(PRINTF))

$(PRINTFERR):
	$(MAKE) -C $(dir $(PRINTFERR))

$(BUILD):
	mkdir -p $(BUILD)

bonus: $(NAME_BONUS)
.PHONY: bonus

$(BUILD_BONUS)/%.o: $(BONUS)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

$(BUILD_BONUS):
	mkdir -p $(BUILD_BONUS)

$(NAME_BONUS): $(BUILD_BONUS) $(OBJS_BONUS) $(LIBFT) $(PRINTF) $(PRINTFERR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS_BONUS) $(LDLIBS) -o $(NAME_BONUS)

clean:
	rm -rf $(BUILD)
	rm -rf $(BUILD_BONUS)
	$(MAKE) -C ./ft_printf clean
	$(MAKE) -C ./ft_printferr clean
	$(MAKE) -C ./libft clean
.PHONY: clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C ./ft_printf fclean
	$(MAKE) -C ./ft_printferr fclean
	$(MAKE) -C ./libft fclean
.PHONY: fclean

run: bonus
	./$(NAME_BONUS) pipex "cat -e" "grep ".c"" outfile

run2: bonus
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME_BONUS) pipex "ls -l -a" "wc -l" outfile

run3:
	ls

re: fclean all
.PHONY: re

rebonus: fclean bonus
.PHONY: rebonus
