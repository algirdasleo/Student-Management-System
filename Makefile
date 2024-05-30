CC=g++ 					# compiler to use
TARGET=run 				# name of the executable
CFLAGS=-O3 				# optimization level
CPPFLAGS=-std=c++11 			# c++ version
TEST_FILES_STUDENTAS=test_studentas.cpp catch_amalgamated.cpp functions.cpp
TEST_FILES_NEWVECTOR=test_newvector.cpp catch_amalgamated.cpp

TEST_TARGET=test_runner
TEST_CPPFLAGS=-std=c++14

build: main.cpp functions.cpp functions.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) main.cpp functions.cpp
run: build
	./$(TARGET)
test_studentas:
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) -o $(TEST_TARGET) $(TEST_FILES_STUDENTAS)
	./$(TEST_TARGET)
test_newvector:
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) -o $(TEST_TARGET) $(TEST_FILES_NEWVECTOR)
	./$(TEST_TARGET)
clean:
	rm -f $(TARGET) $(TEST_TARGET)
