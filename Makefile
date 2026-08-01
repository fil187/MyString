CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -g -lgtest -lgtest_main -o


tests: tests.cpp
	$(CXX) ./tests.cpp $(CXXFLAGS) tests.exe

run: tests
	./tests.exe

clean:
	rm tests.exe