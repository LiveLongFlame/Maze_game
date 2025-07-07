# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lncurses

# Target for building everything together
APP = game
SRCS = main.cpp Maze/maze.cpp Player/player.cpp Scoreboard/score.cpp

$(APP): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(APP) $(LDFLAGS)
	@echo "---------- RUNNING $(APP) ----------"
	./$(APP)

# Pattern rule: make <filename>
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
	@echo "---------- RUNNING $@ ----------"
	./$@

# Default help target
all:
	@echo "Usage:"
	@echo "  make <file>     - Compile single file"
	@echo "  make game       - Compile full project with all modules"
	@echo "  make clean      - Clean up build files"

# Clean rule
clean:
	rm -f *.o *.out *.exe *.gch game

