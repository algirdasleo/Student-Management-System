CC=g++ # compiler to use
TARGET=run # name of the executable
CFLAGS=-O3 # optimization level
CPPFLAGS=-std=c++11 # c++ version
build: main.cpp functions.cpp functions.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) main.cpp functions.cpp
run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
