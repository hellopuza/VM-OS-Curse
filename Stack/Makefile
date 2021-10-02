####

CC = g++
CFLAGS = -c -O3
SOURCES = main.cpp Stack.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Stack

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)


