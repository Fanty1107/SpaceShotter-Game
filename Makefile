# Variáveis do compilador
CXX = clang++
CXXFLAGS = -I./include
LDFLAGS = -L./lib -lraylib -lglfw -lGL -lX11 -lpthread -lXi -lXrandr

# Seus arquivos de código-fonte
SOURCES = src/main.cc

# Nome do executável
TARGET = main

default:
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)