NAME = n_puzzle

CPPFILES = src/n-puzzle.cpp src/heuristic_functions.cpp src/solution_algorithms.cpp

HPPFILES = includes/Puzzle.hpp

OBJFILES = n-puzzle.o heuristic_functions.o solution_algorithms.o

HPPFILES_DIR = includes/

all: $(NAME)

$(NAME): $(CPPFILES) $(HPPFILES)
	clang++ -std=c++17 -I $(HPPFILES_DIR) -c $(CPPFILES)
	clang++ -std=c++17 -I $(HPPFILES_DIR) $(OBJFILES) -o $(NAME)

clean:
	rm -rf $(OBJFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all
