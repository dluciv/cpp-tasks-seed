include ../Makefile.inc

.PHONY: all run_utest run_itest depends clean cleanall

release : sort_demo.r.o
	$(LD) -o $@ $^

debug   : sort_demo.d.o
	$(LD) -o $@ $^

utest   : sort_test.d.o
	$(LD) -o $@ $^ $(GTEST_LIBS)

run_utest : utest
	./$^

run_itest : debug
	@echo "=== Integration tests ==="
	./$^

all: run_utest run_itest

sort_demo.d.o : sort_demo.cpp sorting.h collvalue.h
sort_demo.r.o : sort_demo.cpp sorting.h collvalue.h
sort_test.d.o : sort_test.cpp sorting.h

-include Makefile.hdrdep