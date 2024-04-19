# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 17:54:40 by dukim             #+#    #+#              #
#    Updated: 2024/04/11 17:54:44 by dukim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	libftprintf.a
SRC		= 	ft_printf.c print_type.c print_utils.c format.c buffer_utils.c
OBJS	=	$(SRC:.c=.o)

# ifdef BONUS
# 	FINAL_OBJS = $(OBJS) $(LST_OBJS)
# else
# 	FINAL_OBJS = $(OBJS)
# endif

.PHONY:		all bonus clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		ar -rc $(NAME) $(OBJS)

$(OBJS)	:	$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# $(LST_OBJS)	:	$(LST_SRC)
# 	$(CC) $(CFLAGS) -c $(LST_SRC)

bonus:
	@make BONUS=1 all

clean:
	@rm -f $(OBJS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all
