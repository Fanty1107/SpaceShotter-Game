CXX = clang++
CXXFLAGS = -I./include
LDFLAGS = -L./lib -lraylib -lglfw -lGL -lX11 -lpthread -lXi -lXrandr


SOURCES = src/main.cc src/gameObjects.cc src/raygui.cc

TARGET = main

default:
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)