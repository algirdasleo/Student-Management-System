CC=g++
TARGET=run
CFLAGS=-03
build: main.cpp functions.cpp functions.h
	$(CC) -o $(TARGET) main.cpp functions.cpp -I.

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
