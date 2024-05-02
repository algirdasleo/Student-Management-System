CC=g++ 					# compiler to use
TARGET=run 				# name of the executable
CFLAGS=-O3 				# optimization level
CPPFLAGS=-std=c++11 	# c++ version
TEST_FILES=test_studentas.cpp catch_amalgamated.cpp functions.cpp
TEST_TARGET=test_runner
TEST_CPPFLAGS=-std=c++14

build: main.cpp functions.cpp functions.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) main.cpp functions.cpp
run: build
	./$(TARGET)
test:
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) -o $(TEST_TARGET) $(TEST_FILES)
	./$(TEST_TARGET)
clean:
	rm -f $(TARGET) $(TEST_TARGET)
