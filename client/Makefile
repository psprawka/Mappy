# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/25 09:04:20 by tle-huu-          #+#    #+#              #
#    Updated: 2018/08/12 17:05:05 by tle-huu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = execlient

SRCS = 	srcs/CommunicationSocket.cpp \
		srcs/Datagram.cpp		\
		srcs/utils.cpp				\
		srcs/Graph.class.cpp				\
		srcs/Ai.class.cpp		\
		srcs/Car.cpp			\
		srcs/AStar.cpp \
		main.cpp

INCLUDES = includes/
OBJS = $(SRCS:.cpp=.o)

CXX = clang++
CXXFLAGS += -std=c++11
# CXXFLAGS += -Wall -Wextra -Werror
LDFLAGS +=  -fsanitize=address

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -I . -I $(INCLUDES) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I . -I $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean all
