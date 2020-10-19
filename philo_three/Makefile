NAME	= philo_three
SRCS	= main.c
SRCS	+= args.c
SRCS	+= logger.c
SRCS	+= print.c
SRCS	+= awake.c
SRCS	+= time.c
SRCS	+= philo.c
SRCS	+= philos.c
SRCS	+= watcher.c

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
