CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

.PHONY: all release debug depends tidy astyle clean test utest run_utest run_itest

all: demo

demo: sort_demo.cpp
	$(CXX) $(CXXFLAGS) sort_demo.cpp -o demo

test: sort_test.cpp
	$(CXX) $(CXXFLAGS) sort_test.cpp -lgtest -lgtest_main -pthread -o test
	./test

utest: test

run_utest: utest

run_itest:

release: demo test

debug: CXXFLAGS += -g -O0
debug: demo test

depends:

tidy:

astyle:
	astyle --options=../astyle.ini *.h *.cpp

clean:
	rm -f demo test