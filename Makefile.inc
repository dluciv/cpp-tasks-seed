CXX = g++
GTEST_INCLUDE = -I/opt/homebrew/include
GTEST_LIB_DIR = -L/opt/homebrew/lib
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall $(GTEST_INCLUDE) $(CXX_EXTRA_FLAGS)
CXXFLAGS_R = $(CXXFLAGS) -O3 -DNDEBUG
CXXFLAGS_D = $(CXXFLAGS) -g  -DDEBUG
GTEST_LIBS = -lgtest -lgtest_main -lpthread $(GTEST_LIB_DIR)
LD=$(CXX)

%.d.o : %.cpp
	$(CXX) -c $(CXXFLAGS_D) -o $@ $<

%.r.o : %.cpp
	$(CXX) -c $(CXXFLAGS_R) -o $@ $<

clean :
	- rm *.o
	- rm *.hdrdep.bak

cleanall : clean
	- rm release debug debug_test utest
	- echo > Makefile.hdrdep

mrproper : cleanall

astyle:
	astyle --options=../astyle.ini *.h *.cpp

depends :
	makedepend -f Makefile.hdrdep *.c*