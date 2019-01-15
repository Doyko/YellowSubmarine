CC = g++
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = YellowSubmarine
RM = rm

G_FLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(G_FLAGS)

%.o: %.cpp
	$(CC) $(G_FLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ) $(TARGET)

re: clean $(TARGET)

animation.o: animation.cpp animation.h
bonus.o: bonus.cpp bonus.h player.h entity.h data.h map.h hitbox.h \
 animation.h projectile.h mob.h game.h effect.h buff.h
data.o: data.cpp data.h map.h hitbox.h animation.h entity.h
effect.o: effect.cpp effect.h data.h map.h hitbox.h animation.h entity.h \
 projectile.h mob.h game.h player.h buff.h bonus.h
entity.o: entity.cpp entity.h data.h map.h hitbox.h animation.h
game.o: game.cpp game.h player.h entity.h data.h map.h hitbox.h \
 animation.h projectile.h mob.h effect.h buff.h bonus.h
hitbox.o: hitbox.cpp hitbox.h data.h map.h animation.h entity.h
main.o: main.cpp game.h player.h entity.h data.h map.h hitbox.h \
 animation.h projectile.h mob.h effect.h buff.h bonus.h
map.o: map.cpp map.h data.h hitbox.h entity.h animation.h
mob.o: mob.cpp mob.h data.h map.h hitbox.h animation.h entity.h \
 projectile.h effect.h game.h player.h buff.h bonus.h
player.o: player.cpp player.h entity.h data.h map.h hitbox.h animation.h \
 projectile.h mob.h game.h bonus.h buff.h effect.h
projectile.o: projectile.cpp projectile.h entity.h data.h map.h hitbox.h \
 animation.h mob.h game.h player.h buff.h bonus.h effect.h
