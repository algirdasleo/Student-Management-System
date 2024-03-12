# Define compiler
CC=g++

# Define the target executable
TARGET=run

# Build target
build: main.cpp functions.cpp functions.h
	$(CC) -o $(TARGET) main.cpp functions.cpp -I.

# Run target
run: build
	./$(TARGET)

# Clean target
clean:
	rm -f $(TARGET)
