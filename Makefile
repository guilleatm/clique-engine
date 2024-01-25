PROJECT_NAME = clique-engine
OUTPUT_DIR = build

INCLUDE_DIRS = -I/usr/include/SDL2 -Iinclude/imgui
LIB_DIRS = -Llib

SRC = $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)

default:
	g++ $(SRC) -lSDL2 -o $(OUTPUT_DIR)/$(PROJECT_NAME) $(INCLUDE_DIRS) $(LIB_DIRS)