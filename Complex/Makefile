####

CC = g++
CFLAGS = -c -O3
SOURCES = main.cpp Complex.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Complex

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)


