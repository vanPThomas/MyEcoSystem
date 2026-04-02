EXE = MyEcoSystem
IMGUI_DIR = ./
SOURCES = ./src/main.cpp ./src/UI/UIManager.cpp
SOURCES += $(IMGUI_DIR)/includes/imgui.cpp $(IMGUI_DIR)/includes/imgui_demo.cpp $(IMGUI_DIR)/includes/imgui_draw.cpp $(IMGUI_DIR)/includes/imgui_tables.cpp $(IMGUI_DIR)/includes/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/includes/imgui_impl_glfw.cpp $(IMGUI_DIR)/includes/imgui_impl_opengl3.cpp

OBJS = $(SOURCES:.cpp=.o)

UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -std=c++20 -I$(IMGUI_DIR)/imgui -I$(IMGUI_DIR)/backends -g -Wall -Wformat
LIBS =

ifeq ($(UNAME_S), Linux)
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3 sdl2` -lssl -lcrypto -pthread -ldl -lz
	CXXFLAGS += `pkg-config --cflags glfw3 sdl2`
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32 -lws2_32 -lssl -lcrypto -lSDL2
	CXXFLAGS += `pkg-config --cflags glfw3`
endif

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
ifeq ($(OS), Windows_NT)
	del /f $(EXE) $(OBJS)
else
	rm -f $(EXE) $(OBJS)
endif
