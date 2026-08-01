CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -g -lgtest -lgtest_main


tests: tests.cpp
	$(CXX) ./tests.cpp $(CXXFLAGS) -o tests.exe

run: tests
	./tests --gtest_output=xml:test-results.xml

clean:
	rm tests.exe && rm test-results.xml