PROJECT_NAME = clique-engine
OUTPUT_DIR = build

IMGUI_SUBMODULE = submodules/imgui
FLECS_SUBMODULE = submodules/flecs


INCLUDE_DIRS = -I/usr/include/SDL2 -I$(IMGUI_SUBMODULE) -I$(FLECS_SUBMODULE)/include

LIBS = -lSDL2_image

SRC = $(wildcard src/*.cpp) $(wildcard $(IMGUI_SUBMODULE)/*.cpp) $(wildcard $(IMGUI_SUBMODULE)/src/*.cpp)

default:
	g++ $(SRC) -lSDL2 -o $(OUTPUT_DIR)/$(PROJECT_NAME) $(INCLUDE_DIRS) $(LIBS)