all: compile link compile2


link: ; g++ helloworld.o Game.o State.o MenuState.o GameState.o Board.o player.o Button.o game_info.o Leaderboard.o -o sfml.app -lsfml-graphics -lsfml-window -lsfml-system
compile: ; g++ -c helloworld.cpp -c Game.cpp -c State.cpp -c MenuState.cpp -c GameState.cpp -c Board.cpp -c player.cpp -c Button.cpp -c game_info.cpp -c Leaderboard.cpp
compile2: ; ./sfml.app