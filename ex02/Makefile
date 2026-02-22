NAME = PmergeMe

SRCS = PmergeMe.cpp mergeInsertionSort_vector.cpp mergeInsertionSort_deque.cpp main.cpp
OBJS = ${SRCS:.cpp=.o}
HEADERS = PmergeMe.hpp

INCDIR = .

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INCDIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

debug: fclean
	$(CXX) $(CXXFLAGS) -DDEBUG=true $(SRCS) -o $(NAME) -I $(INCDIR)

re: fclean all

.PHONY: all clean fclean
