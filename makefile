CC = g++
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = YellowSubmarine
RM = rm

G_FLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(G_FLAGS)


%.o: %.c
	$(CC) -c $< -o $@

clean:
	$(RM) -f $(OBJ) $(TARGET)

re: clean $(TARGET)
