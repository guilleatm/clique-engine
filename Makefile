PROJECT_NAME = clique-engine

OUTPUT_DIR = build/

SDL = -I/usr/include/SDL2/
IMGUI = -Isubmodules/imgui/
FLECS = -Isubmodules/flecs/

SRC = $(wildcard src/*.cpp) $(wildcard submodules/imgui/*.cpp) $(wildcard src/Engine/*.cpp)

default:
	g++ $(SRC) -o $(OUTPUT_DIR)$(PROJECT_NAME) -std=c++0x $(SDL) $(IMGUI) $(FLECS) -lSDL2 -lSDL2_image submodules/flecs/flecs.o




# PROJECT_NAME = clique-engine
# OUTPUT_DIR = build

# IMGUI_SUBMODULE = submodules/imgui
# FLECS_SUBMODULE = submodules/flecs


# INCLUDE_DIRS = -I/usr/include/SDL2 -I$(IMGUI_SUBMODULE) -I$(FLECS_SUBMODULE)/include

# LIBS = -lSDL2_image

# SRC = $(wildcard src/*.cpp) $(wildcard $(IMGUI_SUBMODULE)/*.cpp) $(wildcard $(IMGUI_SUBMODULE)/src/*.cpp)

# default:
# 	g++ $(SRC) -lSDL2 -o $(OUTPUT_DIR)/$(PROJECT_NAME) $(INCLUDE_DIRS) $(LIBS)