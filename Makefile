#compilador c++
CXX = g++

#flags
CXXFLAGS = -Wall -Wextra -std=c++11

#nome do programa
TARGET = main

#aquivo fonte
SOURCES = main.cpp

#arquivos objeto
#OBJECTS = $(SOURCES:.cpp=.o)

#all: $(TARGET)

#regra para compilar
$(TARGET) : $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Regra para criar arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos objeto e executável
clean:
	rm -f $(SOURCES) $(TARGET)