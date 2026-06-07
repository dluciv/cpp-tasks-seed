CXX_EXTRA_FLAGS=-I ../external/eigen
LD_EXTRA_OPT=

include ../Makefile.inc

release : gauss

gauss  : Gauss_main.r.o Gauss_solve.r.o
	$(LD) -fopenmp -o $@ $^ $(LD_EXTRA_OPT)

debug   : Gauss_main.d.o Gauss_solve.d.o
	$(LD) -fopenmp -o $@ $^ $(LD_EXTRA_OPT)

utest   : Gauss_test.d.o Gauss_solve.d.o
	$(LD) -fopenmp -o $@ $^ $(GTEST_LIBS)

run_utest : utest
	./utest

run_itest : release
	echo "Integration tests..."
	bash ./integration_test.sh

all: depends run_utest run_itest

include Makefile.hdrdep