

CC = g++
STD = -std=c++20
TARGET = LeitnerBox
SRCS = interface.cpp leitner.cpp getInput.cpp processInput.cpp main.cpp
OBJS = $(SRCS: .cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(STD) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(STD) -c $< -o $@

# excluding processInput from beeing compiled again. because the cpp file included in interface.cpp	