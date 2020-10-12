NAME	= philo_one
SRCS	= main.c
SRCS	+= args.c
SRCS	+= print.c
SRCS	+= forks.c
SRCS	+= awake.c
SRCS	+= time.c
SRCS	+= philo.c

CFLAGS	= -Wall -Wextra -Werror
CC		= clang

OBJDIR	= .objs
OBJS	=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

$(NAME): $(OBJS)
		${CC} ${CFLAGS} -lpthread $(OBJS) -o $(NAME)

all:		$(NAME)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		@mkdir $(OBJDIR)

${OBJDIR}/%.o: %.c
		${CC} ${CFLAGS} -c $< -o $@

clean:
			rm -rf $(OBJDIR)

fclean:	clean
			rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
