PROJECT_NAME = clique-engine

OUTPUT_DIR = build/

SDL = -I/usr/include/SDL2/
IMGUI_DIR = libs/imgui
FLECS_DIR = libs/flecs

IMGUI = -I$(IMGUI_DIR) $(IMGUI_DIR)/imgui.a
FLECS = -I$(FLECS_DIR) $(FLECS_DIR)/flecs.a


SRC = $(wildcard src/editor/*.cpp) $(wildcard src/engine/*.cpp) $(wildcard src/game/*.cpp)

default:
	g++ $(SRC) -o $(OUTPUT_DIR)$(PROJECT_NAME) -std=c++0x $(SDL) $(IMGUI) $(FLECS) -lSDL2 -lSDL2_image




# PROJECT_NAME = clique-engine
# OUTPUT_DIR = build

# IMGUI_SUBMODULE = submodules/imgui
# FLECS_SUBMODULE = submodules/flecs


# INCLUDE_DIRS = -I/usr/include/SDL2 -I$(IMGUI_SUBMODULE) -I$(FLECS_SUBMODULE)/include

# LIBS = -lSDL2_image

# SRC = $(wildcard src/*.cpp) $(wildcard $(IMGUI_SUBMODULE)/*.cpp) $(wildcard $(IMGUI_SUBMODULE)/src/*.cpp)

# default:
# 	g++ $(SRC) -lSDL2 -o $(OUTPUT_DIR)/$(PROJECT_NAME) $(INCLUDE_DIRS) $(LIBS)