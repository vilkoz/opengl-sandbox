NAME = a.out

FLAGS = -lGL -lGLU -lGLEW -lglut -g

SRC = chapter2.c		\
	  shaders.c

BINS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

$(NAME): $(BINS)
	gcc $(FLAGS) -o $(NAME) $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
