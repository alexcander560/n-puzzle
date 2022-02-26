CPPFILES = n-puzzle.cpp

HPPFILES = Puzzle.hpp

OBJFILES = n-puzzle.o

HPPFILES_DIR = .

NAME = n_puzzle

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	clang++ -std=c++17 -I $(HPPFILES_DIR) -c $(CPPFILES)
	clang++ -std=c++17 -I $(HPPFILES_DIR) $(OBJFILES) -o $(NAME)

clean:
	rm -rf $(OBJFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all
